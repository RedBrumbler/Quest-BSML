#include "BSML/Parsing/PrimaryButtonTagParser.hpp"
#include "BSML/Tags/PrimaryButtonTag.hpp"

namespace BSML {
    // instance of parser
    PrimaryButtonTagParser PrimaryButtonTagParser::primaryButtonTagParser;

    PrimaryButtonTagParser::PrimaryButtonTagParser() : BSMLTagParser({"action-button", "primary-button"}) {
    }

    BSMLTag* PrimaryButtonTagParser::newTag() {
        return new PrimaryButtonTag();
    }
}