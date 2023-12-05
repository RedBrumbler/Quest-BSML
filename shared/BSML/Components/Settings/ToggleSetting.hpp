#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/UI/Toggle.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "../../GenericSettingWrapper.hpp"
#include "BaseSetting.hpp"

DECLARE_CLASS_CUSTOM(BSML, ToggleSetting, BSML::BaseSetting,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(GenericSettingWrapper, genericSetting);
        DECLARE_INSTANCE_FIELD(UnityEngine::UI::Toggle, toggle);
        DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI, _text);
        DECLARE_INSTANCE_FIELD(bool, currentValue); /* default: false; */
    );

    FIELD_ACCESSOR(genericSetting);
    FIELD_ACCESSOR(toggle);
    FIELD_ACCESSOR(_text);
    FIELD_ACCESSOR(currentValue);

    DECLARE_INSTANCE_METHOD(bool, get_Value);
    DECLARE_INSTANCE_METHOD(void, set_Value, bool value);
    __declspec(property(get=get_Value, put=set_Value)) bool Value;

    DECLARE_INSTANCE_METHOD(StringW, get_text);
    DECLARE_INSTANCE_METHOD(void, set_text, StringW value);
    __declspec(property(get=get_text, put=set_text)) StringW text;

    DECLARE_INSTANCE_METHOD(bool, get_interactable);
    DECLARE_INSTANCE_METHOD(void, set_interactable, bool value);
    __declspec(property(get=get_interactable, put=set_interactable)) bool interactable;

    DECLARE_INSTANCE_METHOD(void, Setup);
    DECLARE_INSTANCE_METHOD(void, ReceiveValue);
    DECLARE_INSTANCE_METHOD(void, ApplyValue);
    DECLARE_INSTANCE_METHOD(void, OnValueChanged, bool value);

    DECLARE_CTOR(ctor);
)
