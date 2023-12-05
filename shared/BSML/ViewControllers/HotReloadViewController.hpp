#pragma once

#include "custom-types/shared/macros.hpp"
#include "../Components/HotReloadFileWatcher.hpp"
#include "HMUI/ViewController.hpp"

DECLARE_CLASS_CORDL(BSML, HotReloadViewController, HMUI::ViewController,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(HotReloadFileWatcher, fileWatcher);
    );

    FIELD_ACCESSOR(fileWatcher)
    DECLARE_INSTANCE_METHOD(void, Awake);
)
