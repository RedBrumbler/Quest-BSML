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
#include "UnityEngine/TextureWrapMode.hpp"
#include "UnityEngine/Networking/UnityWebRequest.hpp"
#include "UnityEngine/Networking/DownloadHandler.hpp"

#include "csscolorparser.hpp"

#include "System/Uri.hpp"
#include "System/StringComparison.hpp"

#include "custom-types/shared/coroutine.hpp"

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

    std::optional<UnityEngine::Color> ParseHTMLColorOpt(std::string_view str) {
        std::string val{str};
        bool valid = false;
        auto color = CSSColorParser::parse(val);
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
                    if (scaleOptions.shouldScale) {
                        // TODO: downscaling
                    }
                    DEBUG("Loading sprite");
                    auto sprite = LoadSpriteRaw(data);
                    sprite->get_texture()->set_wrapMode(TextureWrapMode::Clamp);
                    DEBUG("setting sprite");
                    image->set_sprite(sprite);
                    INFO("image: {}", fmt::ptr(image));
                    INFO("sprite: {}", fmt::ptr(sprite));

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
}