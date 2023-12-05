#pragma once

#include "custom-types/shared/macros.hpp"
#include "HMUI/ViewController.hpp"
#include "../SettingsMenu.hpp"

DECLARE_CLASS_CORDL(BSML, SettingsMenuListViewController, HMUI::ViewController,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(CustomListTableData, list);
        public:
            std::function<void(SettingsMenu*)> clickedMenu;
    );

    FIELD_ACCESSOR(list);
    FIELD_ACCESSOR(clickedMenu);

    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::ViewController::DidActivate>::get(), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_INSTANCE_METHOD(void, SettingsClick, HMUI::TableView tableView, int idx);

)
