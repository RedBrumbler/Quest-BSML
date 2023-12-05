#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "VRUIControls/VRPointer.hpp"

DECLARE_CLASS_CORDL(BSML, VRPointerEnabledPatch, UnityEngine::MonoBehaviour,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(VRUIControls::VRPointer, _vrPointer);
    );

    FIELD_ACCESSOR(_vrPointer);

    DECLARE_INSTANCE_METHOD(void, Awake);
    DECLARE_INSTANCE_METHOD(void, OnEnable);

    public:
        static UnorderedEventCallback<VRUIControls::VRPointer> OnPointerEnabled;
)
