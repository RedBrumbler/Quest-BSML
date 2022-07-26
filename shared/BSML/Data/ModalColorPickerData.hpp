#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "UnityEngine/Vector2.hpp"
#include "BSML/Components/ModalColorPicker.hpp"

namespace BSML {
    class ModalColorPickerData {
        public:
            ModalColorPickerData() {};
            explicit ModalColorPickerData(const tinyxml2::XMLElement& elem);
            
            std::string_view get_value() const { return value; }
            std::string_view get_onCancel() const { return onCancel; }
            std::string_view get_onDone() const { return onDone; }
            std::string_view get_colorChange() const { return colorChange; }

            void Apply(BSML::ModalColorPicker* colorPicker, Il2CppObject* host) const;
        private:
            std::string value;
            std::string onCancel;
            std::string onDone;
            std::string colorChange;
    };
}