#include "BSML/Parsing/VerticalTagParser.hpp"
#include "BSML/Tags/VerticalTag.hpp"

namespace BSML {
    // instance of parser
    VerticalTagParser VerticalTagParser::verticalParser;

    VerticalTagParser::VerticalTagParser() : BSMLTagParser({"vertical"}) {
    };

    BSMLTag* VerticalTagParser::newTag() {
        return new VerticalTag();
    }
}