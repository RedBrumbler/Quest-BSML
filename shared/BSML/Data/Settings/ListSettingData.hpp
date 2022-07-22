#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "BSML/Components/Settings/ListSetting.hpp"

namespace BSML {
    class ListSettingData {
        public:
            ListSettingData() {};
            explicit ListSettingData(const tinyxml2::XMLElement& elem);
            
            void Apply(BSML::ListSetting* listSetting, Il2CppObject* host) const;
        private:
            /// name of field that contains the list of values
            std::string listOptions;
            /// name of the field that the choice should go in
            std::string listChoice;
    };
}