#pragma once

#include "custom-types/shared/macros.hpp"
#include "../../macros.hpp"
#include "UnityEngine/UI/Button.hpp"
#include <functional>

DECLARE_CLASS_CORDL(BSML, MenuButton, bs_hook::Il2CppWrapperType,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(StringW, text);
        DECLARE_INSTANCE_FIELD(StringW, hoverHint);
        DECLARE_INSTANCE_FIELD(bool, interactable);
        DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button, menuButton);
        private:
            std::function<void(void)> onClick;
    );

    FIELD_ACCESSOR(text);
    FIELD_ACCESSOR(hoverHint);
    FIELD_ACCESSOR(menuButton);
    FIELD_ACCESSOR(onClick);

    DECLARE_INSTANCE_METHOD(bool, get_interactable);
    DECLARE_INSTANCE_METHOD(void, set_interactable, bool value);
    __declspec(property(get=get_interactable, put=set_interactable)) bool value;

    DECLARE_INSTANCE_METHOD(void, Click);

    DECLARE_DEFAULT_CTOR();

    public:
        static MenuButton* Make_new(std::string_view label, std::string_view hoverHint = "", std::function<void()> onClick = nullptr);

)
