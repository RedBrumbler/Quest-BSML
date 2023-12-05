#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/UI/Image.hpp"

#include "AnimationControllerData.hpp"

DECLARE_CLASS_CORDL(BSML, AnimationStateUpdater, UnityEngine::MonoBehaviour,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(UnityEngine::UI::Image, image);
        DECLARE_INSTANCE_FIELD_PRIVATE(AnimationControllerData, _controllerData);
    );

    FIELD_ACCESSOR(image);
    FIELD_ACCESSOR(_controllerData);

    DECLARE_INSTANCE_METHOD(AnimationControllerData, get_controllerData);
    DECLARE_INSTANCE_METHOD(void, set_controllerData, AnimationControllerData value);
    __declspec(property(get=get_controllerData, put=AnimationControllerData)) AnimationControllerData controllerData;

    DECLARE_INSTANCE_METHOD(void, OnEnable);
    DECLARE_INSTANCE_METHOD(void, OnDisable);
    DECLARE_INSTANCE_METHOD(void, OnDestroy);
)
