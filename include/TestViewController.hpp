#pragma once

#include "custom-types/shared/macros.hpp"
#include "HMUI/ViewController.hpp"

#include "UnityEngine/UI/HorizontalLayoutGroup.hpp"
#include "UnityEngine/UI/Button.hpp"

#include "macros.hpp"

DECLARE_CLASS_CODEGEN(BSML, TestViewController, HMUI::ViewController,
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::HorizontalLayoutGroup*, layout);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, goodButton);
    DECLARE_INSTANCE_FIELD(bool, someOtherField);
    DECLARE_INSTANCE_FIELD(ListWrapper<StringW>, someList);

    BSML_PROPERTY_ONCHANGED(StringW, myChoice);
    BSML_PROPERTY_ONCHANGED(bool, testToggle);
    BSML_PROPERTY_ONCHANGED(float, incdecValue);

    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::ViewController::DidActivate>::get(), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

    DECLARE_INSTANCE_METHOD(void, ButtonPressed);
    DECLARE_INSTANCE_METHOD(void, OnPropertiesChanged);
    DECLARE_INSTANCE_METHOD(void, PinkCuteToggled, bool value);

    DECLARE_CTOR(ctor);
    
)