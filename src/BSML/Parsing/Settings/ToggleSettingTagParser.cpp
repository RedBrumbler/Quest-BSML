#include "BSML/Parsing/Settings/ToggleSettingTagParser.hpp"
#include "BSML/Tags/Settings/ToggleSettingTag.hpp"

namespace BSML {
    // instance of parser
    ToggleSettingTagParser ToggleSettingTagParser::toggleSettingTagParser;

    ToggleSettingTagParser::ToggleSettingTagParser() : BSMLTagParser({"toggle-setting", "bool-setting", "checkbox-setting", "checkbox"}) {
    }

    BSMLTag* ToggleSettingTagParser::newTag() {
        return new ToggleSettingTag();
    }
}