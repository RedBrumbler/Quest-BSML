#pragma once

#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "../Components/CustomListTableData.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/Coroutine.hpp"
#include "UI/ModSettingsFlowCoordinator.hpp"

DECLARE_CLASS_CORDL(BSML, BSMLSettings, bs_hook::Il2CppWrapperType,
    DECLARE_FIELD(
        DECLARE_INSTANCE_FIELD(bool, isInitialized);
        DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button, button);
        DECLARE_INSTANCE_FIELD(UnityEngine::Sprite, normal);
        DECLARE_INSTANCE_FIELD(UnityEngine::Sprite, hover);
        DECLARE_INSTANCE_FIELD(ListWrapper<BSML::CustomCellInfo>, _settingsMenus);
        DECLARE_INSTANCE_FIELD(UnityEngine::Coroutine, addButtonCoroutine);
        DECLARE_INSTANCE_FIELD(ModSettingsFlowCoordinator, _modSettingsFlowCoordinator);
    );

    FIELD_ACCESSOR(isInitialized);
    FIELD_ACCESSOR(button);
    FIELD_ACCESSOR(normal);
    FIELD_ACCESSOR(hover);
    FIELD_ACCESSOR(_settingsMenus);
    FIELD_ACCESSOR(addButtonCoroutine);
    FIELD_ACCESSOR(_modSettingsFlowCoordinator);

    DECLARE_INSTANCE_METHOD(ListWrapper<BSML::CustomCellInfo>, get_settingsMenus);
    __declspec(property(get=get_settingsMenus)) ListWrapper<BSML::CustomCellInfo> settingsMenus;

    DECLARE_INSTANCE_METHOD(ModSettingsFlowCoordinator, get_modSettingsFlowCoordinator);
    __declspec(property(get=get_modSettingsFlowCoordinator)) ModSettingsFlowCoordinator modSettingsFlowCoordinator;

    DECLARE_INSTANCE_METHOD(void, Setup);
    DECLARE_INSTANCE_METHOD(void, PresentSettings);

    DECLARE_DEFAULT_CTOR();
    public:
        bool TryAddSettingsMenu(SettingsMenu menu);
        bool TryAddSettingsMenu(std::string_view name, std::string_view content_key, bs_hook::Il2CppWrapperType host, bool showExtraButtons = false);
        bool TryAddSettingsMenu(System::Type csType, std::string_view name, MenuSource menuType, bool showExtraButtons = false);
        bool TryAddSettingsMenu(std::function<void(HMUI::ViewController, bool, bool, bool)> viewControllerDidActivate, std::string_view name, bool showExtraButtons = false);

        bool RemoveSettingsMenu(bs_hook::Il2CppWrapperType host);
        static BSMLSettings get_instance();
    protected:
        void TryAddBSMLMenu();
        custom_types::Helpers::Coroutine AddButtonToMainScreen();
        static SafePtr<BSMLSettings> instance;
)
