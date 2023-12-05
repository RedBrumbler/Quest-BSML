#pragma once

#include "custom-types/shared/macros.hpp"
#include "BaseSetting.hpp"
#include "../../GenericSettingWrapper.hpp"
#include "HMUI/DropdownWithTableView.hpp"
#include "HMUI/SimpleTextDropdown.hpp"

DECLARE_CLASS_CUSTOM(BSML, DropdownListSetting, BSML::BaseSetting,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(GenericSettingWrapper, genericSetting);
        DECLARE_INSTANCE_FIELD(HMUI::SimpleTextDropdown, dropdown);
        DECLARE_INSTANCE_FIELD(ListWrapper<bs_hook::Il2CppWrapperType>, values);
        DECLARE_INSTANCE_FIELD(int, index) = 0;

        public:
            std::function<void(bs_hook::Il2CppWrapperType)> onChange = nullptr;
            std::function<StringW(bs_hook::Il2CppWrapperType)> formatter = nullptr;
    );

    FIELD_ACCESSOR(genericSetting);
    FIELD_ACCESSOR(dropdown);
    FIELD_ACCESSOR(values);
    FIELD_ACCESSOR(index);
    FIELD_ACCESSOR(onChange);
    FIELD_ACCESSOR(formatter);

    DECLARE_INSTANCE_METHOD(bs_hook::Il2CppWrapperType, get_Value);
    DECLARE_INSTANCE_METHOD(void, set_Value, bs_hook::Il2CppWrapperType value);
    __declspec(property(get=get_Value,put=set_Value)) bs_hook::Il2CppWrapperType Value;

    DECLARE_INSTANCE_METHOD(bool, get_interactable);
    DECLARE_INSTANCE_METHOD(void, set_interactable, bool value);
    __declspec(property(get=get_interactable,put=set_interactable)) bool interactable;

    DECLARE_INSTANCE_METHOD(void, Setup);
    DECLARE_INSTANCE_METHOD(void, UpdateChoices);
    DECLARE_INSTANCE_METHOD(void, OnSelectIndex, HMUI::DropdownWithTableView tableView, int index);
    DECLARE_INSTANCE_METHOD(void, ReceiveValue);
    DECLARE_INSTANCE_METHOD(void, ApplyValue);
    DECLARE_INSTANCE_METHOD(void, ValidateRange);
    DECLARE_INSTANCE_METHOD(void, UpdateState);

    DECLARE_CTOR(ctor);
)
