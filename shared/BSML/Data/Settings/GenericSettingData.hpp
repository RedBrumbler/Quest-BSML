#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "BSML/GenericSettingWrapper.hpp"

namespace BSML {
    class GenericSettingData {
        public:
            GenericSettingData() {};
            explicit GenericSettingData(const tinyxml2::XMLElement& elem);
            
            std::string_view get_onChange() const { return onChange; }
            std::string_view get_value() const { return value; }
            auto get_applyOnChange() const { return applyOnChange; }

            void Apply(BSML::GenericSettingWrapper* genericSetting, Il2CppObject* host) const;
        private:
            std::string onChange;
            std::string value;
            std::optional<bool> applyOnChange;
    };
}