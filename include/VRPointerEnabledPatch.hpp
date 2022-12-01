#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "VRUIControls/VRPointer.hpp"

DECLARE_CLASS_CODEGEN(BSML, VRPointerEnabledPatch, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_FIELD(VRUIControls::VRPointer*, _vrPointer);
    DECLARE_INSTANCE_METHOD(void, Awake);
    DECLARE_INSTANCE_METHOD(void, OnEnable);

    public:
        static UnorderedEventCallback<VRUIControls::VRPointer*> OnPointerEnabled;
)