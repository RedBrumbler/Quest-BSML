#include "BSML/Parsing/Settings/StringSettingTagParser.hpp"
#include "BSML/Tags/Settings/StringSettingTag.hpp"

namespace BSML {
    // instance of parser
    StringSettingTagParser StringSettingTagParser::stringSettingTagParser;

    StringSettingTagParser::StringSettingTagParser() : BSMLTagParser({"string-setting"}) {
    }

    BSMLTag* StringSettingTagParser::newTag() {
        return new StringSettingTag();
    }
}