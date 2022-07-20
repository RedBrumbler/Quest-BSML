#include "BSML/Parsing/ButtonTagParser.hpp"
#include "BSML/Tags/ButtonTag.hpp"

namespace BSML {
    // instance of parser
    ButtonTagParser ButtonTagParser::buttonTagParser;

    ButtonTagParser::ButtonTagParser() : BSMLTagParser({"button"}) {
    }

    BSMLTag* ButtonTagParser::newTag() {
        return new ButtonTag();
    }
}