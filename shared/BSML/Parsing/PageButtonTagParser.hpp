#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"

namespace BSML {
    class PageButtonTagParser : private BSMLTagParser {
        private:
            PageButtonTagParser();
            virtual BSMLTag* newTag() override;

            static PageButtonTagParser pageButtonTagParser;
    };
}