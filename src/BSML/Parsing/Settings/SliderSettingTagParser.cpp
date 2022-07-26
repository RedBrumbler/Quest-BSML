#include "BSML/Parsing/Settings/SliderSettingTagParser.hpp"
#include "BSML/Tags/Settings/SliderSettingTag.hpp"

namespace BSML {
    // instance of parser
    SliderSettingTagParser SliderSettingTagParser::sliderSettingTagParser;

    SliderSettingTagParser::SliderSettingTagParser() : BSMLTagParser({"slider-setting"}) {
    }

    BSMLTag* SliderSettingTagParser::newTag() {
        return new SliderSettingTag();
    }
}