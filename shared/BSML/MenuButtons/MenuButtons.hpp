#pragma once

#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "HMUI/Screen.hpp"
#include "MenuButton.hpp"
#include "MenuButtonsViewController.hpp"
#include "UnityEngine/Coroutine.hpp"

DECLARE_CLASS_CORDL(BSML, MenuButtons, bs_hook::Il2CppWrapperType,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(MenuButtonsViewController, menuButtonsViewController);
        DECLARE_INSTANCE_FIELD(HMUI::Screen, leftScreen);
        DECLARE_INSTANCE_FIELD(ListWrapper<bs_hook::Il2CppWrapperType>, _buttons);
        DECLARE_INSTANCE_FIELD(UnityEngine::Coroutine, presentViewCoroutine);
    );

    FIELD_ACCESSOR(menuButtonsViewController);
    FIELD_ACCESSOR(leftScreen);
    FIELD_ACCESSOR(_buttons);
    FIELD_ACCESSOR(presentViewCoroutine);

    DECLARE_INSTANCE_METHOD(ListWrapper<bs_hook::Il2CppWrapperType>, get_buttons);
    __declspec(property(get=get_buttons)) ListWrapper<bs_hook::Il2CppWrapperType> buttons;

    DECLARE_INSTANCE_METHOD(bool, Registerbutton, MenuButton button);
    DECLARE_INSTANCE_METHOD(bool, UnRegisterbutton, MenuButton button);
    DECLARE_INSTANCE_METHOD(void, Setup);
    DECLARE_INSTANCE_METHOD(void, Refresh);
    DECLARE_INSTANCE_METHOD(void, ShowView, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

    DECLARE_DEFAULT_CTOR();
    public:
        static MenuButtons get_instance();
        custom_types::Helpers::Coroutine PresentView();
    protected:
        static SafePtr<MenuButtons> instance;
)
