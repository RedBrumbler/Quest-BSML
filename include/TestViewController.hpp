#pragma once

#include "custom-types/shared/macros.hpp"
#include "HMUI/ViewController.hpp"

#include "BSML/Components/ModalView.hpp"
#include "BSML/Components/CustomListTableData.hpp"
#include "UnityEngine/UI/HorizontalLayoutGroup.hpp"
#include "UnityEngine/UI/Button.hpp"

#include "CustomListObject.hpp"

#include "macros.hpp"

DECLARE_CLASS_CODEGEN(BSML, TestViewController, HMUI::ViewController,
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::HorizontalLayoutGroup*, layout);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, goodButton);
    DECLARE_INSTANCE_FIELD(bool, someOtherField);
    DECLARE_INSTANCE_FIELD(ListWrapper<StringW>, someList);
    DECLARE_INSTANCE_FIELD(ListWrapper<StringW>, sliderList);
    DECLARE_INSTANCE_FIELD(ListWrapper<CustomCellInfo*>, listData);
    DECLARE_INSTANCE_FIELD(ListWrapper<Il2CppObject*>, customListData);
    DECLARE_INSTANCE_FIELD(BSML::ModalView*, listModal);
    
    BSML_OPTIONS_LIST(lyrics, "Never", "Gonna", "Give", "You", "Up");
    BSML_OPTIONS_LIST(textSegments, "Modded", "Vanilla", "Chocolate", "Strawberry", "Gasoline");
    DECLARE_INSTANCE_FIELD(StringW, sliderChoice);

    BSML_PROPERTY_ONCHANGED(StringW, myChoice);
    BSML_PROPERTY_ONCHANGED(bool, testToggle);
    BSML_PROPERTY_ONCHANGED(float, incdecValue);
    
    BSML_MODAL_METHOD(scare);
    BSML_MODAL_METHOD(mykb);
    DECLARE_INSTANCE_FIELD(float, _length);
    DECLARE_INSTANCE_METHOD(float, get_length);
    DECLARE_INSTANCE_METHOD(void, set_length, float value);
    DECLARE_INSTANCE_METHOD(void, GibString, StringW value);

    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::ViewController::DidActivate>::get(), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

    DECLARE_INSTANCE_METHOD(void, ButtonPressed);
    DECLARE_INSTANCE_METHOD(void, OnPropertiesChanged);
    DECLARE_INSTANCE_METHOD(void, PinkCuteToggled, bool value);
    DECLARE_INSTANCE_METHOD(void, ChangeLength, float value);
    DECLARE_INSTANCE_METHOD(void, GibColor, UnityEngine::Color value);
    DECLARE_INSTANCE_METHOD(void, TextClick);
    DECLARE_INSTANCE_METHOD(void, ShowListModal);
    DECLARE_INSTANCE_METHOD(void, ListElementSelected, HMUI::TableView*, int idx);
    DECLARE_INSTANCE_METHOD(void, SegmentedControlSelect, Il2CppObject* segmentedControl, int index);

    DECLARE_CTOR(ctor);
    
)