#pragma once

#include "custom-types/shared/macros.hpp"
#include "HMUI/ViewController.hpp"
#include "UnityEngine/Transform.hpp"

DECLARE_CLASS_CODEGEN(BSML, MenuButtonsViewController, HMUI::ViewController,
    DECLARE_INSTANCE_FIELD(ListWrapper<Il2CppObject*>, buttons);
    DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, root);
    DECLARE_INSTANCE_METHOD(bool, get_anyButtons);
    DECLARE_INSTANCE_METHOD(void, RefreshView);

    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::ViewController::DidActivate>::get(), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
)