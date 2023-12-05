#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/Vector2.hpp"

namespace BSML {
    class Keyboard;
}

DECLARE_CLASS_CORDL(BSML, Key, bs_hook::Il2CppWrapperType,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(StringW, name);
        DECLARE_INSTANCE_FIELD(StringW, value);
        DECLARE_INSTANCE_FIELD(StringW, shifted);
        DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button, button);

        /* kb here is not declared as a Keyboard directly, because size constraints */
        DECLARE_INSTANCE_FIELD(bs_hook::Il2CppWrapperType, kb);

        std::function<void(Key*)> keyAction = nullptr;
    );

    FIELD_ACCESSOR(name);
    FIELD_ACCESSOR(value);
    FIELD_ACCESSOR(shifted);
    FIELD_ACCESSOR(button);
    FIELD_ACCESSOR(keyAction);

    /* special field accessor because we have a weird field here */
    Keyboard get_kb();
    void set_kb(Keyboard value);
    __declspec(property(get=get_kb, put=set_kb)) Keyboard kb;

    DECLARE_DEFAULT_CTOR();
    public:
        void OnClick();
        bool KeyAction();
        bool Enter();

        Key Set(StringW value);
        static Key construct();
        static Key construct(Keyboard kb, UnityEngine::Vector2 position, StringW text, float width, float height, UnityEngine::Color color);

)
