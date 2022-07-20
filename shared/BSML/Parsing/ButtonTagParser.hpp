#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"

namespace BSML {
    class BSMLTagParser;
    class BSMLDocParser;

    class ButtonTagParser : private BSMLTagParser {
        private:
            ButtonTagParser();
            virtual BSMLTag* newTag() override;

            static ButtonTagParser buttonTagParser;
    };
}