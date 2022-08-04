#include "Helpers/utilities.hpp"
#include "BSMLDataCache_internal.hpp"
#include "logging.hpp"

#include "GlobalNamespace/SharedCoroutineStarter.hpp"
#include "System/Collections/Generic/Dictionary_2.hpp" 
#include "UnityEngine/ImageConversion.hpp"
#include "UnityEngine/Rect.hpp"
#include "UnityEngine/SpriteMeshType.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Texture.hpp"
#include "UnityEngine/FilterMode.hpp"
#include "UnityEngine/Texture2D.hpp"
#include "UnityEngine/Graphics.hpp"
#include "UnityEngine/RenderTexture.hpp"
#include "UnityEngine/RenderTextureFormat.hpp"
#include "UnityEngine/RenderTextureReadWrite.hpp"
#include "UnityEngine/TextureWrapMode.hpp"
#include "UnityEngine/Networking/UnityWebRequest.hpp"
#include "UnityEngine/Networking/DownloadHandler.hpp"

#include "csscolorparser.hpp"

#include "System/Uri.hpp"
#include "System/StringComparison.hpp"

#include "custom-types/shared/coroutine.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"

#define coro(coroutine) GlobalNamespace::SharedCoroutineStarter::get_instance()->StartCoroutine(custom_types::Helpers::CoroutineHelper::New(coroutine))

using namespace UnityEngine;
using namespace UnityEngine::Networking;

namespace BSML::Utilities {


    template<typename T, typename U>
    using Dictionary = System::Collections::Generic::Dictionary_2<T, U>;

    SafePtr<Dictionary<StringW, UnityEngine::Sprite*>> spriteCache;
    Sprite* FindSpriteCached(StringW name) {
        if (!spriteCache)
            spriteCache.emplace(Dictionary<StringW, UnityEngine::Sprite*>::New_ctor());
        
        UnityEngine::Sprite* sprite = nullptr;

        if (spriteCache->TryGetValue(name, byref(sprite)) && sprite && Object::IsNativeObjectAlive(sprite))
            return sprite;

        for (auto x : Resources::FindObjectsOfTypeAll<Sprite*>())
        {
            if (x->get_name()->get_Length() == 0)
                continue;
            UnityEngine::Sprite* a = nullptr;
            if(!spriteCache->TryGetValue(x->get_name(), byref(a)) || !a)
                spriteCache->Add(x->get_name(), x);

            if (x->get_name() == name)
                sprite = x;
        }

        return sprite;
    }

    SafePtr<Dictionary<StringW, UnityEngine::Texture*>> textureCache;
    Texture* FindTextureCached(StringW name) {
        if (!textureCache)
            textureCache.emplace(Dictionary<StringW, UnityEngine::Texture*>::New_ctor());
        
        UnityEngine::Texture* texture = nullptr;

        if (textureCache->TryGetValue(name, byref(texture)) && texture && Object::IsNativeObjectAlive(texture))
            return texture;

        for (auto x : Resources::FindObjectsOfTypeAll<Texture*>())
        {
            if (x->get_name()->get_Length() == 0)
                continue;
            UnityEngine::Texture* a = nullptr;
            if(!textureCache->TryGetValue(x->get_name(), byref(a)) || !a)
                textureCache->Add(x->get_name(), x);

            if (x->get_name() == name)
                texture = x;
        }

        return texture;
    }

    std::optional<UnityEngine::Color> ParseHTMLColorOpt(std::string_view str) {
        std::string val{str};
        bool valid = false;
        auto color = CSSColorParser::parse(val, valid);
        if (!valid) return std::nullopt;
        return UnityEngine::Color{
            (float)color.r / 255.0f,
            (float)color.g / 255.0f,
            (float)color.b / 255.0f,
            color.a
        };
    }

    UnityEngine::Color ParseHMTMLColor(std::string_view str) {
        return ParseHTMLColorOpt(str).value_or(UnityEngine::Color{1.0, 1.0, 1.0, 1.0});
    }

    std::optional<UnityEngine::Color32> ParseHTMLColor32Opt(std::string_view str) {
        std::string val{str};
        bool valid = false;
        auto color = CSSColorParser::parse(val, valid);
        if (!valid) return std::nullopt;
        return UnityEngine::Color32{
            color.r,
            color.g,
            color.b,
            static_cast<uint8_t>(color.a * 255)
        };
    }

    UnityEngine::Color32 ParseHTMLColor32(std::string_view str) {
        return ParseHTMLColor32Opt(str).value_or(UnityEngine::Color32{255, 255, 255, 255});
    }

    Texture2D* DownScaleTexture(Texture2D* tex, const ScaleOptions& options) {
        auto originalWidth = tex->get_width();
        auto originalHeight = tex->get_height();

        if (originalWidth + originalHeight <= options.width + options.height)
            return tex;

        auto newWidth = options.width;
        auto newHeight = options.height;
        if (options.maintainRatio) {
            auto ratio = (float)originalWidth / (float)originalHeight;
            auto scale = originalWidth > originalHeight ? originalWidth : originalHeight;

            if (scale * ratio <= originalWidth) {
                originalWidth = scale * ratio;
                originalHeight = scale;
            } else {
                originalWidth = scale;
                originalHeight = scale * ratio;
            }
        }

        auto rect = Rect(0, 0, newWidth, newHeight);
        auto copy = Texture2D::New_ctor(rect.get_width(), rect.get_height(), TextureFormat::RGBA32, false);
        auto currentRT = RenderTexture::get_active();
        auto renderTexture = RenderTexture::GetTemporary(rect.get_width(), rect.get_height(), 32, RenderTextureFormat::Default, RenderTextureReadWrite::Default);
        Graphics::Blit(tex, renderTexture);
    
        RenderTexture::set_active(renderTexture);
        copy->ReadPixels(rect, 0, 0);
        copy->Apply();
        RenderTexture::set_active(currentRT);
        RenderTexture::ReleaseTemporary(renderTexture);
        return copy;
    }
    
    UnityEngine::Sprite* DownScaleSprite(Sprite* sprite, const ScaleOptions& options) {
        return LoadSpriteFromTexture(DownScaleTexture(sprite->get_texture(), options));
    }

    custom_types::Helpers::Coroutine GetDataCoroutine(System::Uri* uri, std::function<void(ArrayW<uint8_t>)> onFinished) {
        if (!onFinished) {
            ERROR("Can't get data async without a callback to use it with");
            co_return;
        }
        auto www = UnityWebRequest::Get(uri);
        co_yield reinterpret_cast<System::Collections::IEnumerator*>(www->SendWebRequest());
        if (onFinished) onFinished(www->get_downloadHandler()->GetData());
        co_return;
    }

    void GetData(System::Uri* uri, std::function<void(ArrayW<uint8_t>)> onFinished) {
        INFO("Getting data from uri: {}", uri->get_LocalPath());
        if (!onFinished) {
            ERROR("Can't get data async without a callback to use it with");
            return;
        }
        coro(GetDataCoroutine(uri, onFinished));
    }

    void GetData(StringW key, std::function<void(ArrayW<uint8_t>)> onFinished) {
        INFO("Getting data from key: {}", key);
        auto entry = DataCache::Get(key);
        if (entry) {
            onFinished(entry->get_data());
        } else {
            ERROR("Could not find entry for key: {}", key);
        }
    }

    bool IsAnimated(StringW str)
    {
        return str->EndsWith(".gif", System::StringComparison::OrdinalIgnoreCase) || str->EndsWith(".apng", System::StringComparison::OrdinalIgnoreCase);
    }

    void SetImage(UnityEngine::UI::Image* image, StringW path) {
        SetImage(image, path, true, ScaleOptions());
    }

    SafePtr<Dictionary<StringW, UnityEngine::Sprite*>> imageCache;
    void SetImage(UnityEngine::UI::Image* image, StringW path, bool loadingAnimation, ScaleOptions scaleOptions, std::function<void()> onFinished) {
        INFO("Setting image {}", path);
        if (path->get_Length() > 1 && path[0] == '#') { // it's a base game sprite that is requested
            auto imgName = path->Substring(1);
            image->set_sprite(FindSpriteCached(imgName));

            if (image->get_sprite() == nullptr)
                ERROR("Could not find base game Sprite with image name {}", imgName);
            return;
        }

        if (!imageCache) imageCache.emplace(Dictionary<StringW, UnityEngine::Sprite*>::New_ctor());
        
        UnityEngine::Sprite* sprite = nullptr;
        if (spriteCache->TryGetValue(path, byref(sprite)) && sprite && Object::IsNativeObjectAlive(sprite)) {
            // we got a sprite, use it
            image->set_sprite(sprite);
            if (onFinished) onFinished();
            return;
        } else {
            imageCache->Remove(path);
        }

        System::Uri* uri;
        bool isUri = System::Uri::TryCreate(path, System::UriKind::Absolute, byref(uri));
        // animated just means ".gif || .apng"
        // TODO: support for animated sprites in the future
        if (IsAnimated(path) || (isUri && IsAnimated(uri->get_LocalPath()))) {
            ERROR("Can't load animated images yet!");
        } else { // not animated
            auto onDataFinished = [path, onFinished, image, scaleOptions](ArrayW<uint8_t> data) {
                DEBUG("Data was gotten");
                if (data.Length() > 0) {
                    auto texture = LoadTextureRaw(data);
                    if (scaleOptions.shouldScale) {
                        auto scaledTexture = DownScaleTexture(texture, scaleOptions);
                        if (scaledTexture != texture) {
                            Object::DestroyImmediate(texture);
                            texture = scaledTexture;
                        }
                    }
                    auto sprite = LoadSpriteFromTexture(texture);
                    sprite->get_texture()->set_wrapMode(TextureWrapMode::Clamp);
                    image->set_sprite(sprite);
                    spriteCache->Add(path, sprite);
                }

                if (onFinished)
                    onFinished();
                DEBUG("Done!");
            };

            if (isUri) {
                GetData(uri, onDataFinished);
            } else {
                GetData(path, onDataFinished);
            }
        }
    }

    UnityEngine::Texture2D* LoadTextureRaw(ArrayW<uint8_t> data) {
        if (data.Length() > 0) {
            auto texture = Texture2D::New_ctor(0, 0, TextureFormat::RGBA32, false, false);
            if (ImageConversion::LoadImage(texture, data, false))
                return texture;
        }
        ERROR("Failed to load texture from data");
        return nullptr;
    }

    UnityEngine::Sprite* LoadSpriteRaw(ArrayW<uint8_t> data, float pixelsPerUnit) {
        return LoadSpriteFromTexture(LoadTextureRaw(data), pixelsPerUnit);
    }

    UnityEngine::Sprite* LoadSpriteFromTexture(UnityEngine::Texture2D* texture, float pixelsPerUnit) {
        if (!texture) {
            ERROR("Invalid Texture given");
            return nullptr;
        }
        return Sprite::Create(texture, Rect(0.0f, 0.0f, texture->get_width(), texture->get_height()), Vector2(0.5f, 0.5f), pixelsPerUnit, 1u, SpriteMeshType::FullRect, Vector4(0.0f, 0.0f, 0.0f, 0.0f), false);
    }

    bool CheckIfClassIsParentClass(const Il2CppClass* klass, const Il2CppClass* possibleParent) {
        while (klass->parent) {
            if (klass->parent == possibleParent) return true;
            klass = klass->parent;
        }
        return false;
    }

    Il2CppObject* CopyFieldsAndProperties(UnityEngine::Component* comp, UnityEngine::Component* other, Il2CppClass* klass) {
        if (!klass) return comp;
        if (!CheckIfClassIsParentClass(comp->klass, klass) && !CheckIfClassIsParentClass(other->klass, klass)) {
            return nullptr;
        }

        void* myIter = nullptr;
        const PropertyInfo* prop = nullptr;
        while((prop = il2cpp_functions::class_get_properties(klass, &myIter))) {
            if (prop->get && prop->set) {
                auto getter = il2cpp_functions::property_get_get_method(prop);
                auto setter = il2cpp_functions::property_get_set_method(prop);
                if ((getter->token & METHOD_ATTRIBUTE_STATIC) == METHOD_ATTRIBUTE_STATIC) continue;
                if ((setter->token & METHOD_ATTRIBUTE_STATIC) == METHOD_ATTRIBUTE_STATIC) continue;

                std::array<void*, 1> args{nullptr};
                Il2CppException* exp = nullptr;
                auto value = il2cpp_functions::runtime_invoke(getter, other, args.data(), &exp);
                if (exp) {
                    // handle an exception
                    ERROR("Exception: {}", exp->message);
                    continue;
                }
                args[0] = value;
                il2cpp_functions::runtime_invoke(setter, comp, args.data(), &exp);
                if (exp) {
                    // handle an exception
                    ERROR("Exception: {}", exp->message);
                    continue;
                }
            }
        }
        
        myIter = nullptr;
        ::FieldInfo* field = nullptr;
        void* value = nullptr;
        uint32_t size = 0;
        while((field = il2cpp_functions::class_get_fields(klass, &myIter))) {
            if ((field->token & FIELD_ATTRIBUTE_STATIC) == FIELD_ATTRIBUTE_STATIC) continue;
            auto klass = il2cpp_functions::Class_FromIl2CppType(const_cast<Il2CppType*>(field->type));
            size = klass->instance_size;
            value = realloc(value, size);
            il2cpp_functions::field_get_value(other, field, value);
            il2cpp_functions::field_set_value(comp, field, value);
        }
        free(value);

        return CopyFieldsAndProperties(comp, other, klass->parent);
    }
    
    /// based on https://answers.unity.com/questions/530178/how-to-get-a-component-from-an-object-and-add-it-t.html
    UnityEngine::Component* GetCopyOfComponent(UnityEngine::Component* comp, UnityEngine::Component* other) {
        auto klass = comp->klass;
        if (klass != other->klass) {
            ERROR("Type Mismatch!");
            return nullptr;
        }

        return reinterpret_cast<UnityEngine::Component*>(CopyFieldsAndProperties(comp, other, klass));
    }

    /// end of based on thing

    namespace ImageResources {
        UnityEngine::Sprite* blankSprite = nullptr;
        UnityEngine::Sprite* GetBlankSprite() {
            if (!blankSprite || !Object::IsNativeObjectAlive(blankSprite)) {
                auto texture = Texture2D::get_blackTexture();
                blankSprite = Sprite::Create(texture, Rect(0.0f, 0.0f, texture->get_width(), texture->get_height()), Vector2(0.5f, 0.5f), 100.0f, 1u, SpriteMeshType::FullRect, Vector4(0.0f, 0.0f, 0.0f, 0.0f), false);
                blankSprite->set_name("BlankSprite");
                Object::DontDestroyOnLoad(blankSprite);
            }
            return blankSprite;
        }
        
        UnityEngine::Sprite* whitePixelSprite = nullptr;
        UnityEngine::Sprite* GetWhitePixel() {
            if (!whitePixelSprite || !Object::IsNativeObjectAlive(whitePixelSprite)) {
                FindSpriteCached("WhitePixel");
            }
            return whitePixelSprite;
        }
    }
}