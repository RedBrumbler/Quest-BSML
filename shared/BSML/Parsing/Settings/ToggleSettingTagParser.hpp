#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"

namespace BSML {
    class ToggleSettingTagParser : private BSMLTagParser {
        private:
            ToggleSettingTagParser();
            virtual BSMLTag* newTag() override;

            static ToggleSettingTagParser toggleSettingTagParser;
    };
}