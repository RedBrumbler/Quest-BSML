#pragma once

#include "custom-types/shared/macros.hpp"
#include "BSML/Components/Settings/BaseSetting.hpp"
#include "BSML/GenericSettingWrapper.hpp"
#include "HMUI/DropdownWithTableView.hpp"
#include "HMUI/SimpleTextDropdown.hpp"

DECLARE_CLASS_CUSTOM(BSML, DropdownListSetting, BSML::BaseSetting,
    DECLARE_INSTANCE_FIELD(GenericSettingWrapper*, genericSetting);
    DECLARE_INSTANCE_FIELD(HMUI::SimpleTextDropdown*, dropdown);
    DECLARE_INSTANCE_FIELD(ListWrapper<Il2CppObject*>, values);
    DECLARE_INSTANCE_FIELD(int, index);                             /* default: 0; */
    
    DECLARE_INSTANCE_METHOD(Il2CppObject*, get_Value);
    DECLARE_INSTANCE_METHOD(void, set_Value, Il2CppObject* value);

    DECLARE_INSTANCE_METHOD(bool, get_interactable);
    DECLARE_INSTANCE_METHOD(void, set_interactable, bool value);

    DECLARE_INSTANCE_METHOD(void, Setup);
    DECLARE_INSTANCE_METHOD(void, UpdateChoices);
    DECLARE_INSTANCE_METHOD(void, OnSelectIndex, HMUI::DropdownWithTableView* tableView, int index);
    DECLARE_INSTANCE_METHOD(void, ReceiveValue);
    DECLARE_INSTANCE_METHOD(void, ApplyValue);
    DECLARE_INSTANCE_METHOD(void, ValidateRange);
    DECLARE_INSTANCE_METHOD(void, UpdateState);

    DECLARE_CTOR(ctor);

    public:
        std::function<StringW(Il2CppObject*)> formatter = nullptr;
)