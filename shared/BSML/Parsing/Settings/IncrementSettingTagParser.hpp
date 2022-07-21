#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"
#include "BSML/Tags/Settings/IncDecSettingTag.hpp"
#include "BSML/Components/Settings/IncrementSetting.hpp"
#include "questui/shared/CustomTypes/Components/Settings/IncrementSetting.hpp"

namespace BSML {
    class IncrementSettingTagParser : private BSMLTagParser {
        public:
            using IncrementSettingTag = IncDecSettingTag<BSML::IncrementSetting*>;
        private:
            IncrementSettingTagParser();
            virtual BSMLTag* newTag() override;

            static IncrementSettingTagParser incrementSettingTagParser;
    };
}