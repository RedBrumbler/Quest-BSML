#include "Helpers/utilities.hpp"

#include "System/Collections/Generic/Dictionary_2.hpp" 
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/Resources.hpp"

#include "csscolorparser.hpp"

using namespace UnityEngine;

namespace BSML::Utilities {


    template<typename T, typename U>
    using Dictionary = System::Collections::Generic::Dictionary_2<T, U>;

    SafePtr<Dictionary<StringW, UnityEngine::Sprite*>> spriteCache;
    Sprite* FindSpriteCached(StringW name) {
        if (!spriteCache)
            spriteCache.emplace(Dictionary<StringW, UnityEngine::Sprite*>::New_ctor());
        
        UnityEngine::Sprite* sprite = nullptr;

        if (spriteCache->TryGetValue(name, byref(sprite)) && sprite)
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
}