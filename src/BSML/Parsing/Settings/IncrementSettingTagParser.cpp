#include "BSML/Parsing/Settings/IncrementSettingTagParser.hpp"

namespace BSML {
    // instance of parser
    IncrementSettingTagParser IncrementSettingTagParser::incrementSettingTagParser;

    IncrementSettingTagParser::IncrementSettingTagParser() : BSMLTagParser({"increment-setting"}) {
    }

    BSMLTag* IncrementSettingTagParser::newTag() {
        return new IncrementSettingTag();
    }
}