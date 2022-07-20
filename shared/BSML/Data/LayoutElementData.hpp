#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"

namespace BSML {
    class LayoutElementData {
        public:
            LayoutElementData() {};
            explicit LayoutElementData(const tinyxml2::XMLElement& elem);
            
            auto get_ignoreLayout() const { return ignoreLayout; };
            UnityEngine::Vector2 get_preferredSize() const { return {preferredWidth.value_or(0), preferredHeight.value_or(0)}; };
            UnityEngine::Vector2 get_minimumSize() const { return {minimumWidth.value_or(0), minimumHeight.value_or(0)}; };
            
            auto get_preferredWidth() const { return preferredWidth; };
            auto get_preferredHeight() const { return preferredHeight; };
            auto get_minimumWidth() const { return minimumWidth; };
            auto get_minimumHeight() const { return minimumHeight; };

            void Apply(UnityEngine::UI::LayoutElement* layoutElement) const;
        private:
            std::optional<bool> ignoreLayout;
            std::optional<float> preferredWidth;
            std::optional<float> preferredHeight;
            std::optional<float> minimumWidth;
            std::optional<float> minimumHeight;
    };
}