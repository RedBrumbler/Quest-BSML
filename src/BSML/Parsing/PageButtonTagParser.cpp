#include "BSML/Parsing/PageButtonTagParser.hpp"
#include "BSML/Tags/PageButtonTag.hpp"

namespace BSML {
    // instance of parser
    PageButtonTagParser PageButtonTagParser::pageButtonTagParser;

    PageButtonTagParser::PageButtonTagParser() : BSMLTagParser({"page-button", "pg-button"}) {
    }

    BSMLTag* PageButtonTagParser::newTag() {
        return new PageButtonTag();
    }
}