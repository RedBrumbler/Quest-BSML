#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "BSML/Components/PageButton.hpp"

namespace BSML {
    class PageButtonData {
        public:
            PageButtonData() {};

            auto get_pageButtonDirection() const { return pageButtonDirection; }
            enum class PageButtonDirection {
                Up,
                Down,
                Left,
                Right
            };

            explicit PageButtonData(const tinyxml2::XMLElement& elem);
            void Apply(BSML::PageButton* button) const;
        private:

            PageButtonDirection pageButtonDirection;

    };
}