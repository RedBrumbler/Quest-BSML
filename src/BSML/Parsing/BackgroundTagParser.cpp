#include "BSML/Parsing/BackgroundTagParser.hpp"
#include "BSML/Tags/BackgroundTag.hpp"

namespace BSML {
    // instance of parser
    BackgroundTagParser BackgroundTagParser::backgroundTagParser;

    BackgroundTagParser::BackgroundTagParser() : BSMLTagParser({"background", "bg", "div"}) {
    }

    BSMLTag* BackgroundTagParser::newTag() {
        return new BackgroundTag();
    }
}