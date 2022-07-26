#include "BSML/Parsing/Settings/SubmenuTagParser.hpp"
#include "BSML/Tags/Settings/SubmenuTag.hpp"

namespace BSML {
    // instance of parser
    SubmenuTagParser SubmenuTagParser::submenuTagParser;

    SubmenuTagParser::SubmenuTagParser() : BSMLTagParser({"settings-submenu"}) {
    }

    BSMLTag* SubmenuTagParser::newTag() {
        return new SubmenuTag();
    }
}