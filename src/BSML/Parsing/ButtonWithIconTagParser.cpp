#include "BSML/Parsing/ButtonWithIconTagParser.hpp"
#include "BSML/Tags/ButtonWithIconTag.hpp"

namespace BSML {
    // instance of parser
    ButtonWithIconTagParser ButtonWithIconTagParser::buttonWithIconTagParser;

    ButtonWithIconTagParser::ButtonWithIconTagParser() : BSMLTagParser({"button-with-icon", "icon-button"}) {
    }

    BSMLTag* ButtonWithIconTagParser::newTag() {
        return new ButtonWithIconTag();
    }
}