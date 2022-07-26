#include "BSML/Parsing/Settings/ListSliderSettingTagParser.hpp"
#include "BSML/Tags/Settings/ListSliderSettingTag.hpp"

namespace BSML {
    // instance of parser
    ListSliderSettingTagParser ListSliderSettingTagParser::listSliderSettingTagParser;

    ListSliderSettingTagParser::ListSliderSettingTagParser() : BSMLTagParser({"list-slider-setting"}) {
    }

    BSMLTag* ListSliderSettingTagParser::newTag() {
        return new ListSliderSettingTag();
    }
}