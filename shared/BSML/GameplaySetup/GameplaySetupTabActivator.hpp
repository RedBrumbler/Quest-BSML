#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "../MenuSource.hpp"

DECLARE_CLASS_CORDL(BSML, GameplaySetupTabActivator, UnityEngine::MonoBehaviour,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(MenuSource, menuSource);
        DECLARE_INSTANCE_FIELD(UnityEngine::MonoBehaviour, mb);
        DECLARE_INSTANCE_FIELD(bool, _activatedBefore);
        public:
            std::function<void(UnityEngine::GameObject*, bool)> didActivate;
    );

    FIELD_ACCESSOR(menuSource);
    FIELD_ACCESSOR(mb);
    FIELD_ACCESSOR(_activatedBefore);
    FIELD_ACCESSOR(didActivate);

    DECLARE_INSTANCE_METHOD(void, OnEnable);
    DECLARE_INSTANCE_METHOD(void, OnDisable);
)
