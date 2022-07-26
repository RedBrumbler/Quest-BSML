#include "BSML/Parsing/ModalTagParser.hpp"
#include "BSML/Tags/ModalTag.hpp"
    
namespace BSML {
    // instance of parser
    ModalTagParser ModalTagParser::modalParser;

    ModalTagParser::ModalTagParser() : BSMLTagParser({"modal"}) {
    };

    BSMLTag* ModalTagParser::newTag() {
        return new ModalTag();
    }
}

