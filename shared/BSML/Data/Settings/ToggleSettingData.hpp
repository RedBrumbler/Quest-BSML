#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "BSML/Components/Settings/ToggleSetting.hpp"

namespace BSML {
    class ToggleSettingData {
        public:
            ToggleSettingData() {};
            explicit ToggleSettingData(const tinyxml2::XMLElement& elem);
            
            auto get_onText() const { return onText; }
            auto get_offText() const { return offText; }
            
            void Apply(BSML::ToggleSetting* toggleSetting, Il2CppObject* host) const;
        private:
            std::optional<std::string> onText;
            std::optional<std::string> offText;
    };
}