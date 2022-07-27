#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "UnityEngine/UI/Image.hpp"
namespace BSML {
    class ImageData {
        public:
            ImageData() {};
            explicit ImageData(const tinyxml2::XMLElement& elem);
            
            void Apply(UnityEngine::UI::Image* button) const;
        private:
    };
}