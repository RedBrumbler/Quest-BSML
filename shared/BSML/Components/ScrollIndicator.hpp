#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "HMUI/VerticalScrollIndicator.hpp"

DECLARE_CLASS_CORDL(BSML, ScrollIndicator, HMUI::VerticalScrollIndicator,
    DECLARE_FIELDS();
    DECLARE_INSTANCE_METHOD(UnityEngine::RectTransform, get_Handle);
    DECLARE_INSTANCE_METHOD(void, set_Handle, UnityEngine::RectTransform value);
    __declspec(property(get=get_Handle, put=set_Handle)) UnityEngine::RectTransform Handle;
)
