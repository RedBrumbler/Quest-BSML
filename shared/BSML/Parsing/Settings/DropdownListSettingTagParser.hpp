#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"

namespace BSML {
    class DropdownListSettingTagParser : private BSMLTagParser {
        private:
            DropdownListSettingTagParser();
            virtual BSMLTag* newTag() override;

            static DropdownListSettingTagParser dropdownListSettingTagParser;
    };
}