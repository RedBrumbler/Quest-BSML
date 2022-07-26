#include "BSML/Parsing/Settings/ColorSettingTagParser.hpp"
#include "BSML/Tags/Settings/ColorSettingTag.hpp"

namespace BSML {
    // instance of parser
    ColorSettingTagParser ColorSettingTagParser::colorSettingTagParser;

    ColorSettingTagParser::ColorSettingTagParser() : BSMLTagParser({"color-setting"}) {
    }

    BSMLTag* ColorSettingTagParser::newTag() {
        return new ColorSettingTag();
    }
}