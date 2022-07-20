#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/UI/HorizontalOrVerticalLayoutGroup.hpp"

namespace BSML {
    class HorizontalOrVerticalLayoutGroupData {
        public:
            HorizontalOrVerticalLayoutGroupData() {};
            explicit HorizontalOrVerticalLayoutGroupData(const tinyxml2::XMLElement& elem);
            
            auto get_spacing() const { return spacing; };
            auto get_childExpandWidth() const { return childExpandWidth; };
            auto get_childExpandHeight() const { return childExpandHeight; };
            auto get_childControlWidth() const { return childControlWidth; };
            auto get_childControlHeight() const { return childControlHeight; };

            void Apply(UnityEngine::UI::HorizontalOrVerticalLayoutGroup* horizontalOrVerticalLayoutGroup) const;
        private:
            std::optional<float> spacing;
            std::optional<bool> childExpandWidth;
            std::optional<bool> childExpandHeight;
            std::optional<bool> childControlWidth;
            std::optional<bool> childControlHeight;
    };
}