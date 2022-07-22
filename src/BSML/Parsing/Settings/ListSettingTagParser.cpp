#include "BSML/Parsing/Settings/ListSettingTagParser.hpp"

namespace BSML {
    // instance of parser
    ListSettingTagParser ListSettingTagParser::listSettingTagParser;

    ListSettingTagParser::ListSettingTagParser() : BSMLTagParser({"list-setting"}) {
    }

    BSMLTag* ListSettingTagParser::newTag() {
        return new ListSettingTag();
    }
}