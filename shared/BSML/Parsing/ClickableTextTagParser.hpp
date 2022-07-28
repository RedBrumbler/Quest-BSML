#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"

namespace BSML {
    class ClickableTextTagParser : public BSMLTagParser {
        private:
            ClickableTextTagParser();
            virtual BSMLTag* newTag() override;

            static ClickableTextTagParser clickableTextTagParser;
    };
}