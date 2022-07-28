#include "BSML/Parsing/ClickableTextTagParser.hpp"
#include "BSML/Tags/ClickableTextTag.hpp"
    
namespace BSML {
    // instance of parser
    ClickableTextTagParser ClickableTextTagParser::clickableTextTagParser;

    ClickableTextTagParser::ClickableTextTagParser() : BSMLTagParser({"clickable-text"}) {
    };

    BSMLTag* ClickableTextTagParser::newTag() {
        return new ClickableTextTag();
    }
}

