#include "BSML/Parsing/HorizontalTagParser.hpp"
#include "BSML/Tags/HorizontalTag.hpp"
    
namespace BSML {
    // instance of parser
    HorizontalTagParser HorizontalTagParser::horizontalParser;

    HorizontalTagParser::HorizontalTagParser() : BSMLTagParser({"horizontal"}) {
    };

    BSMLTag* HorizontalTagParser::newTag() {
        return new HorizontalTag();
    }
}

