#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"

namespace BSML {
    class GridLayoutTagParser : private BSMLTagParser {
        private:
            GridLayoutTagParser();
            virtual BSMLTag* newTag() override;

            static GridLayoutTagParser gridLayoutTagParser;
    };
}