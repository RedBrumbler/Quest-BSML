#pragma once

#include <string>
#include "tinyxml2/shared/tinyxml2.h"

namespace BSML {
    class Tree {
        public:
            static Tree parse(std::string_view str);
        
            Tree(std::string_view str);
        private:
            tinyxml2::XMLDocument doc;
    };
}