#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "BSML/Components/Settings/SliderSettingBase.hpp"

namespace BSML {
    class SliderSettingBaseData {
        public:
            SliderSettingBaseData() {};
            explicit SliderSettingBaseData(const tinyxml2::XMLElement& elem);
            
            auto get_showButtons() const { return showButtons; }

            void Apply(BSML::SliderSettingBase* sliderSetting) const;
        private:
            std::optional<bool> showButtons;
    };
}