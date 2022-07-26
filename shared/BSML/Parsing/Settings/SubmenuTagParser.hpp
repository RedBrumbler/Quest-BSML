#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"

namespace BSML {
    class SubmenuTagParser : private BSMLTagParser {
        private:
            SubmenuTagParser();
            virtual BSMLTag* newTag() override;

            static SubmenuTagParser submenuTagParser;
    };
}