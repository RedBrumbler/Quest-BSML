#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "UnityEngine/UI/Selectable.hpp"

namespace BSML {
    class SelectableData {
        public:
            SelectableData() {};
            explicit SelectableData(const tinyxml2::XMLElement& elem);
            
            auto get_interactable() const { return interactable; }
            void Apply(UnityEngine::UI::Selectable* button) const;
        private:
            bool interactable = true;
    };
}