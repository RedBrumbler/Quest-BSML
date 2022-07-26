#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"

namespace BSML
{
    class ScrollIndicatorTagParser : private BSMLTagParser
    {
    private:
        ScrollIndicatorTagParser();
        virtual BSMLTag *newTag() override;

        static ScrollIndicatorTagParser scrollIndicatorTagParser;
    };
}