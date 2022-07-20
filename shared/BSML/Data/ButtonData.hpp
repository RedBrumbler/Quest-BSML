#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "UnityEngine/UI/Button.hpp"

namespace BSML {
    class ButtonData {
        public:
            ButtonData() {};
            explicit ButtonData(const tinyxml2::XMLElement& elem);
            
            auto get_onClick() const { return onClick; }
            void Apply(UnityEngine::UI::Button* button, Il2CppObject* host) const;
        private:
            std::string onClick;
    };
}