#include "BSML/Parsing/ModalKeyboardTagParser.hpp"
#include "BSML/Tags/ModalKeyboardTag.hpp"
    
namespace BSML {
    // instance of parser
    ModalKeyboardTagParser ModalKeyboardTagParser::modalKeyboardParser;

    ModalKeyboardTagParser::ModalKeyboardTagParser() : BSMLTagParser({"modal-keyboard"}) {
    };

    BSMLTag* ModalKeyboardTagParser::newTag() {
        return new ModalKeyboardTag();
    }
}

