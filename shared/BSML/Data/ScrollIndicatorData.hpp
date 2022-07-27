#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "HMUI/VerticalScrollIndicator.hpp"
#include "UnityEngine/Sprite.hpp"

namespace BSML {
    class ScrollIndicatorData {
        public:
            ScrollIndicatorData() {};
            explicit ScrollIndicatorData(const tinyxml2::XMLElement& elem);
            
            // auto get_source() const { return sourceImage }
            auto get_preserveAspect() const { return preserveAspect; }
            void Apply(HMUI::VerticalScrollIndicator* indicator) const;
        private:
            // TODO: Fix this shit
            // StringW sourceImage = "";
            bool preserveAspect = true;
    };
}