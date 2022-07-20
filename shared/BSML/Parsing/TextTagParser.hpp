#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"

namespace BSML {
    class TextTagParser : private BSMLTagParser {
        private:
            TextTagParser();
            virtual BSMLTag* newTag() override;

            static TextTagParser textParser;
    };
}