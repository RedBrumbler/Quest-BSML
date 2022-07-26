#include "BSML/Parsing/ScrollIndicatorTagParser.hpp"
#include "BSML/Tags/ScrollIndicatorTag.hpp"

namespace BSML
{
    ScrollIndicatorTagParser ScrollIndicatorTagParser::scrollIndicatorTagParser;

    ScrollIndicatorTagParser::ScrollIndicatorTagParser() : BSMLTagParser({"vertical-scroll-indicator", "scroll-indicator"}){};

    BSMLTag *ScrollIndicatorTagParser::newTag()
    {
        return new ScrollIndicatorTag();
    };
}