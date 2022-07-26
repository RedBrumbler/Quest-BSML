#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"
#include "BSML/Tags/Settings/ListSettingTag.hpp"
#include "BSML/Components/Settings/ListSetting.hpp"

namespace BSML {
    class ListSettingTagParser : private BSMLTagParser {
        private:
            ListSettingTagParser();
            virtual BSMLTag* newTag() override;

            static ListSettingTagParser listSettingTagParser;
    };
}