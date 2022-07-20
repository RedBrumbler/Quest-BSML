#include "BSML/Parsing/TextTagParser.hpp"
#include "BSML/Tags/TextTag.hpp"
    
namespace BSML {
    // instance of parser
    TextTagParser TextTagParser::textParser;

    TextTagParser::TextTagParser() : BSMLTagParser({ "text", "label" }) {
    };

    BSMLTag* TextTagParser::newTag() {
        return new TextTag();
    }
}

