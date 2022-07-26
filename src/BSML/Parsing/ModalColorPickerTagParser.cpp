#include "BSML/Parsing/ModalColorPickerTagParser.hpp"
#include "BSML/Tags/ModalColorPickerTag.hpp"
    
namespace BSML {
    // instance of parser
    ModalColorPickerTagParser ModalColorPickerTagParser::modalColorPickerTagParser;

    ModalColorPickerTagParser::ModalColorPickerTagParser() : BSMLTagParser({"modal-color-picker"}) {
    };

    BSMLTag* ModalColorPickerTagParser::newTag() {
        return new ModalColorPickerTag();
    }
}

