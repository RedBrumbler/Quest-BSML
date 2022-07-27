#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "BSML/Components/ButtonIconImage.hpp"

namespace BSML {
    class ButtonIconImageData {
        public:
            ButtonIconImageData() {};
            explicit ButtonIconImageData(const tinyxml2::XMLElement& elem);
            
            std::string_view get_icon() const { return icon; }

            void Apply(BSML::ButtonIconImage* buttonIconImage) const;
        private:
            std::string icon;
    };
}