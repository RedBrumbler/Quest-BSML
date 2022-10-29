#pragma once

#include "VRUIControls/VRPointer.hpp"

namespace BSML {
    class VRPointerEnabledPatch {
        public:
            static UnorderedEventCallback<VRUIControls::VRPointer*> OnPointerEnabled;
    };
}