#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"

namespace BSML {
    class StringSettingTagParser : private BSMLTagParser {
        private:
            StringSettingTagParser();
            virtual BSMLTag* newTag() override;

            static StringSettingTagParser stringSettingTagParser;
    };
}