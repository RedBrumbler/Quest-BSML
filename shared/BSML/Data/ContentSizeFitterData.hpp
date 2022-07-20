#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "UnityEngine/UI/ContentSizeFitter.hpp"
#include <optional>

namespace BSML {
    class ContentSizeFitterData {
        public:
            ContentSizeFitterData() {};
            explicit ContentSizeFitterData(const tinyxml2::XMLElement& elem);
            
            auto get_horizontalFit() const { return horizontalFit; }
            auto get_verticalFit() const { return verticalFit; }

            void Apply(UnityEngine::UI::ContentSizeFitter* contentSizeFitter) const;
        private:
            std::optional<UnityEngine::UI::ContentSizeFitter::FitMode> horizontalFit;
            std::optional<UnityEngine::UI::ContentSizeFitter::FitMode> verticalFit;
    };
}