#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "UnityEngine/UI/Toggle.hpp"

namespace BSML {
    class ToggleSettingData {
        public:
            ToggleSettingData() {};
            explicit ToggleSettingData(const tinyxml2::XMLElement& elem);
            
            auto get_onText() const { return onText; }
            auto get_offText() const { return offText; }
            auto get_fieldName() const { return fieldName; }
            auto get_onChange() const { return onChange; }
            auto get_propertyName() const { return propertyName; }
            auto get_startValue() const { return startValue; }
            
            void Apply(UnityEngine::UI::Toggle* toggle, Il2CppObject* host) const;
        private:
            // designed to be used in tandem, fieldName should be the name of the field in the host class, onChange a void method on host
            std::optional<std::string> onText;
            std::optional<std::string> offText;

            std::string fieldName;
            std::string onChange;

            // this should be used if you want to use a property (getter and setter)
            std::string propertyName;
            bool startValue = false;
    };
}