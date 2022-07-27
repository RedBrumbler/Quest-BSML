#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"

namespace BSML {
    class BSMLTagParser;
    class BSMLDocParser;

    class ButtonWithIconTagParser : private BSMLTagParser {
        private:
            ButtonWithIconTagParser();
            virtual BSMLTag* newTag() override;

            static ButtonWithIconTagParser buttonWithIconTagParser;
    };
}