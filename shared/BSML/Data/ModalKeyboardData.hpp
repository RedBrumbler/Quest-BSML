#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "BSML/Components/Keyboard/ModalKeyboard.hpp"

namespace BSML {
    class ModalKeyboardData {
        public:
            ModalKeyboardData() {};
            explicit ModalKeyboardData(const tinyxml2::XMLElement& elem);
            
            std::string_view get_value() const { return value; }
            std::string_view get_onEnter() const { return onEnter; }
            auto get_clearOnOpen() const { return clearOnOpen; }

            void Apply(BSML::ModalKeyboard* modalKeyboard, Il2CppObject* host) const;
        private:
            std::string value;
            std::string onEnter;
            std::optional<bool> clearOnOpen;
    };
}