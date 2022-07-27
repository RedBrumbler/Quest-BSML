#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"

namespace BSML {
    class BSMLTagParser;
    class BSMLDocParser;

    class PrimaryButtonTagParser : private BSMLTagParser {
        private:
            PrimaryButtonTagParser();
            virtual BSMLTag* newTag() override;

            static PrimaryButtonTagParser primaryButtonTagParser;
    };
}