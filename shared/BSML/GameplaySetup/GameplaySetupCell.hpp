#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/TableCell.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "GameplaySetupMenu.hpp"
#include "../Components/Settings/ToggleSetting.hpp"

DECLARE_CLASS_CORDL(BSML, GameplaySetupCell, HMUI::TableCell,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(GameplaySetupMenu, tab);
        DECLARE_INSTANCE_FIELD(ToggleSetting, toggle);
    );

    FIELD_ACCESSOR(tab);
    FIELD_ACCESSOR(toggle);

    DECLARE_INSTANCE_METHOD(GameplaySetupCell*, PopulateCell, GameplaySetupMenu* menu);
    DECLARE_INSTANCE_METHOD(StringW, get_name);
    __declspec(property(get=get_name)) StringW name;
    DECLARE_INSTANCE_METHOD(bool, get_visible);
    DECLARE_INSTANCE_METHOD(void, set_visible, bool value);
    __declspec(property(get=get_visible,put=set_visible)) bool visible;

    DECLARE_DEFAULT_CTOR();
)
