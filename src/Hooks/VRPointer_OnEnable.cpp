#include "hooking.hpp"
#include "VRPointerEnabledPatch.hpp"

UnorderedEventCallback<VRUIControls::VRPointer*> BSML::VRPointerEnabledPatch::OnPointerEnabled;

MAKE_AUTO_HOOK_MATCH(VRPointer_OnEnable, &VRUIControls::VRPointer::OnEnable, void, VRUIControls::VRPointer* self) {
    VRPointer_OnEnable(self);
    if (BSML::VRPointerEnabledPatch::OnPointerEnabled.size() > 0)
        BSML::VRPointerEnabledPatch::OnPointerEnabled.invoke(self);
}