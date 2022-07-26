#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"
#include "BSML/Tags/Settings/IncrementSettingTag.hpp"

namespace BSML {
    class IncrementSettingTagParser : private BSMLTagParser {
        private:
            IncrementSettingTagParser();
            virtual BSMLTag* newTag() override;

            static IncrementSettingTagParser incrementSettingTagParser;
    };
}