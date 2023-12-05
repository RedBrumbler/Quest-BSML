#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "HMUI/RangeValuesTextSlider.hpp"
#include "../../GenericSettingWrapper.hpp"
#include "BaseSetting.hpp"

DECLARE_CLASS_CUSTOM(BSML, SliderSettingBase, BSML::BaseSetting,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(GenericSettingWrapper, genericSetting);
        DECLARE_INSTANCE_FIELD(HMUI::RangeValuesTextSlider, slider);
        DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI, text);
        DECLARE_INSTANCE_FIELD(bool, showButtons);

        DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button, incButton);
        DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button, decButton);

        DECLARE_INSTANCE_FIELD(bool, _enableDec);
        DECLARE_INSTANCE_FIELD(bool, _enableInc);
    );

    FIELD_ACCESSOR(genericSetting);
    FIELD_ACCESSOR(slider);
    FIELD_ACCESSOR(text);
    FIELD_ACCESSOR(showButtons);
    FIELD_ACCESSOR(incButton);
    FIELD_ACCESSOR(decButton);
    FIELD_ACCESSOR(_enableDec);
    FIELD_ACCESSOR(_enableInc);

    DECLARE_INSTANCE_METHOD(bool, get_interactable);
    DECLARE_INSTANCE_METHOD(void, set_interactable, bool value);
    __declspec(property(get=get_interactable, put=set_interactable)) bool interactable;

    DECLARE_INSTANCE_METHOD(void, set_enableDec, bool value);
    DECLARE_INSTANCE_METHOD(void, set_enableInc, bool value);
    __declspec(property(put=set_enableDec)) bool enableDec;
    __declspec(property(put=set_enableInc)) bool enableDec;

    DECLARE_INSTANCE_METHOD(void, BaseSetup);
    DECLARE_CTOR(construct);
)
