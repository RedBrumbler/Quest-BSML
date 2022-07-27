#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"

namespace BSML {
    class BackgroundTagParser : private BSMLTagParser {
        private:
            BackgroundTagParser();
            virtual BSMLTag* newTag() override;
            
            static BackgroundTagParser backgroundTagParser;
    };
}