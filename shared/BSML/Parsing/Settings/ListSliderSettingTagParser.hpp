#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"
#include "BSML/Tags/Settings/ListSliderSettingTag.hpp"

namespace BSML {
    class ListSliderSettingTagParser : private BSMLTagParser {
        private:
            ListSliderSettingTagParser();
            virtual BSMLTag* newTag() override;

            static ListSliderSettingTagParser listSliderSettingTagParser;
    };
}