#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"

namespace BSML {
    class ColorSettingTagParser : private BSMLTagParser {
        private:
            ColorSettingTagParser();
            virtual BSMLTag* newTag() override;

            static ColorSettingTagParser colorSettingTagParser;
    };
}