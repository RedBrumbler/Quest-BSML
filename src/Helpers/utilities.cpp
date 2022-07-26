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

    std::optional<UnityEngine::Color> ParseHMTMLColorOpt(std::string_view str) {
        std::string val{str};
        auto colorOpt = CSSColorParser::parse(val);
        if (!colorOpt.has_value()) return std::nullopt;
        auto value = colorOpt.value();
        return UnityEngine::Color{
            (float)value.r / 255.0f,
            (float)value.g / 255.0f,
            (float)value.b / 255.0f,
            value.a
        };
    }

    UnityEngine::Color ParseHMTMLColor(std::string_view str) {
        return ParseHMTMLColorOpt(str).value_or(UnityEngine::Color{1.0, 1.0, 1.0, 1.0});
    }

    std::optional<UnityEngine::Color32> ParseHMTMLColor32Opt(std::string_view str) {
        std::string val{str};
        auto colorOpt = CSSColorParser::parse(val);
        if (!colorOpt.has_value()) return std::nullopt;
        auto value = colorOpt.value();
        return UnityEngine::Color32{
            value.r,
            value.g,
            value.b,
            static_cast<uint8_t>(value.a * 255)
        };
    }

    UnityEngine::Color32 ParseHMTMLColor32(std::string_view str) {
        return ParseHMTMLColor32Opt(str).value_or(UnityEngine::Color32{255, 255, 255, 255});
    }
}