#pragma once

#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/coroutine.hpp"

#include "HMUI/ScrollView.hpp"

#include "UnityEngine/MonoBehaviour.hpp"

DECLARE_CLASS_CORDL(BSML, ScrollViewContent, UnityEngine::MonoBehaviour,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(HMUI::ScrollView, scrollView);
        DECLARE_INSTANCE_FIELD(bool, dirty);
    )

    DECLARE_INSTANCE_METHOD(void, Start);
    DECLARE_INSTANCE_METHOD(void, OnEnable);
    DECLARE_INSTANCE_METHOD(void, OnRectTransformDimensionsChange);
    DECLARE_INSTANCE_METHOD(void, Update);
    DECLARE_INSTANCE_METHOD(void, UpdateScrollView);

    public:
        custom_types::Helpers::Coroutine SetupScrollView();

)
