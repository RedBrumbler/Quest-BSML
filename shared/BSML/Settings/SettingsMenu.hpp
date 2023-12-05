#pragma once

#include "custom-types/shared/macros.hpp"
#include "HMUI/FlowCoordinator.hpp"
#include "HMUI/ViewController.hpp"
#include "../Components/CustomListTableData.hpp"
#include "../Parsing/BSMLParserParams.hpp"
#include "../MenuSource.hpp"

DECLARE_CLASS_CUSTOM(BSML, SettingsMenu, CustomCellInfo,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(StringW, name);
        DECLARE_INSTANCE_FIELD(StringW, content_key);
        DECLARE_INSTANCE_FIELD(bs_hook::Il2CppWrapperType, host);
        DECLARE_INSTANCE_FIELD(bool, enableExtraButtons);
        DECLARE_INSTANCE_FIELD(HMUI::ViewController, _viewController);
        DECLARE_INSTANCE_FIELD(HMUI::FlowCoordinator, flowCoordinator);
        DECLARE_INSTANCE_FIELD(System::Type, csType);
        DECLARE_INSTANCE_FIELD(MenuSource, menuSource);

        std::shared_ptr<BSMLParserParams> parserParams;
        std::function<void(HMUI::ViewController, bool, bool, bool)> viewControllerDidActivate;
    );

    FIELD_ACCESSOR(name);
    FIELD_ACCESSOR(content_key);
    FIELD_ACCESSOR(host);
    FIELD_ACCESSOR(enableExtraButtons);
    FIELD_ACCESSOR(_viewController);
    FIELD_ACCESSOR(flowCoordinator);
    FIELD_ACCESSOR(csType);
    FIELD_ACCESSOR(menuSource);
    FIELD_ACCESSOR(parserParams);
    FIELD_ACCESSOR(viewControllerDidActivate);

    DECLARE_INSTANCE_METHOD(HMUI::ViewController, get_viewController);
    __declspec(property(get=get_viewController)) HMUI::ViewController viewController;

    DECLARE_INSTANCE_METHOD(void, Setup);
    DECLARE_INSTANCE_METHOD(bool, get_didSetup);
    __declspec(property(get=get_didSetup)) bool didSetup;

    DECLARE_DEFAULT_CTOR();
    DECLARE_SIMPLE_DTOR();

    public:
        static SettingsMenu Make_new(std::string_view name, std::string_view content_key, bs_hook::Il2CppWrapperType host, bool enableExtraButtons = false);
        static SettingsMenu Make_new(std::string_view name, System::Type viewControllerType, MenuSource menuSource, bool enableExtraButtons = false);
        static SettingsMenu Make_new(std::string_view name, std::function<void(HMUI::ViewController, bool, bool, bool)> viewControllerDidActivate, bool enableExtraButtons);

        std::string_view get_content();
        static void SetupViewControllerTransform(HMUI::ViewController viewController);
)
