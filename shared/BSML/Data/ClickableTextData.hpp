#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "BSML/Components/ClickableText.hpp"
namespace BSML {
    class ClickableTextData {
        public:
            ClickableTextData() {};
            explicit ClickableTextData(const tinyxml2::XMLElement& elem);
            
            auto get_defaultColor() const { return defaultColor; }
            auto get_highlightColor() const { return highlightColor; }
            std::string_view get_onClick() const { return onClick; }

            void Apply(BSML::ClickableText* clickableText, Il2CppObject* host) const;
        private:
            std::optional<UnityEngine::Color> defaultColor;
            std::optional<UnityEngine::Color> highlightColor;

            std::string onClick;
    };
}