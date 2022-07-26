#include "BSML/Parsing/Settings/DropdownListSettingTagParser.hpp"
#include "BSML/Tags/Settings/DropdownListSettingTag.hpp"

namespace BSML {
    // instance of parser
    DropdownListSettingTagParser DropdownListSettingTagParser::dropdownListSettingTagParser;

    DropdownListSettingTagParser::DropdownListSettingTagParser() : BSMLTagParser({"dropdown-list-setting"}) {
    }

    BSMLTag* DropdownListSettingTagParser::newTag() {
        return new DropdownListSettingTag();
    }
}