#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"

namespace BSML {
    class HorizontalTagParser : private BSMLTagParser {
        private:
            HorizontalTagParser();
            virtual BSMLTag* newTag() override;

            static HorizontalTagParser horizontalParser;
    };
}