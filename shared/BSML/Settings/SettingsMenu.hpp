#pragma once

#include "custom-types/shared/macros.hpp"
#include "HMUI/ViewController.hpp"
#include "../Components/CustomListTableData.hpp"
#include "../Parsing/BSMLParserParams.hpp"

DECLARE_CLASS_CUSTOM(BSML, SettingsMenu, CustomCellInfo,
    DECLARE_INSTANCE_FIELD(StringW, name);
    DECLARE_INSTANCE_FIELD(StringW, content_key);
    DECLARE_INSTANCE_FIELD(Il2CppObject*, host);
    DECLARE_INSTANCE_FIELD(bool, enableExtraButtons);
    DECLARE_INSTANCE_FIELD(HMUI::ViewController*, viewController);
    DECLARE_INSTANCE_METHOD(HMUI::ViewController*, get_viewController);

    DECLARE_INSTANCE_METHOD(void, Setup);
    DECLARE_INSTANCE_METHOD(bool, get_didSetup);

    DECLARE_DEFAULT_CTOR();
    DECLARE_SIMPLE_DTOR();

    public:
        static SettingsMenu* Make_new(std::string_view name, std::string_view content_key, Il2CppObject* host, bool enableExtraButtons = false);
        std::string_view get_content();
        std::shared_ptr<BSMLParserParams> parserParams;
        static void SetupViewControllerTransform(HMUI::ViewController* viewController);
)