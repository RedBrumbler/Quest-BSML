#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"

namespace BSML {
    class VerticalTagParser : private BSMLTagParser {
        private:
            VerticalTagParser();
            virtual BSMLTag* newTag() override;
            
            static VerticalTagParser verticalParser;
    };
}