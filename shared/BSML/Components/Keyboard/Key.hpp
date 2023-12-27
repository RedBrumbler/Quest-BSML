#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/Vector2.hpp"
#include "../../../typedefs.hpp"

namespace BSML {
    class Keyboard;
}

DECLARE_CLASS_CODEGEN(BSML, Key, System::Object,
    DECLARE_INSTANCE_FIELD(SStringW, name);
    DECLARE_INSTANCE_FIELD(SStringW, value);
    DECLARE_INSTANCE_FIELD(SStringW, shifted);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, button);
    DECLARE_INSTANCE_FIELD(System::Object*, _kb);
    Keyboard* get_kb();
    Keyboard const* get_kb() const;
    void set_kb(Keyboard* value);
    __declspec(property(get=get_kb, put=set_kb)) Keyboard* kb;

    DECLARE_DEFAULT_CTOR();
    public:
        void OnClick();
        bool KeyAction();
        bool Enter();

        Key* Set(SStringW value);
        static Key* construct();
        static Key* construct(Keyboard* kb, UnityEngine::Vector2 position, SStringW text, float width, float height, UnityEngine::Color color);

        std::function<void(Key*)> keyAction = nullptr;
)
