#include "BSML/Parsing/GridLayoutTagParser.hpp"
#include "BSML/Tags/GridLayoutTag.hpp"
    
namespace BSML {
    // instance of parser
    GridLayoutTagParser GridLayoutTagParser::gridLayoutTagParser;

    GridLayoutTagParser::GridLayoutTagParser() : BSMLTagParser({"grid"}) {
    };

    BSMLTag* GridLayoutTagParser::newTag() {
        return new GridLayoutTag();
    }
}

