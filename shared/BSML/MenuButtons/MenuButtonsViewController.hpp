#pragma once

#include "custom-types/shared/macros.hpp"
#include "HMUI/ViewController.hpp"
#include "UnityEngine/Transform.hpp"

DECLARE_CLASS_CORDL(BSML, MenuButtonsViewController, HMUI::ViewController,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(ListWrapper<bs_hook::Il2CppWrapperType>, buttons);
        DECLARE_INSTANCE_FIELD(UnityEngine::Transform, root);
    );

    FIELD_ACCESSOR(buttons);
    FIELD_ACCESSOR(root);

    DECLARE_INSTANCE_METHOD(bool, get_anyButtons);
    __declspec(property(get=get_anyButtons)) bool anyButtons;
    DECLARE_INSTANCE_METHOD(void, RefreshView);

    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::ViewController::DidActivate>::get(), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
)
