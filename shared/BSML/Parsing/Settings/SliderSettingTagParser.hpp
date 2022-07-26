#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"
#include "BSML/Tags/Settings/SliderSettingTag.hpp"

namespace BSML {
    class SliderSettingTagParser : private BSMLTagParser {
        private:
            SliderSettingTagParser();
            virtual BSMLTag* newTag() override;

            static SliderSettingTagParser sliderSettingTagParser;
    };
}