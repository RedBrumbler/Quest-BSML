#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/Vector2.hpp"

namespace BSML {
    class Keyboard;
}

#define DECLARE_INSTANCE_FIELD_TYPENAME(type_, name_, namezpace_, klass_)   \
private:                                                                    \
struct ___FieldRegistrator_##name_ : ::custom_types::FieldRegistrator {     \
    ___FieldRegistrator_##name_() {                                         \
        ___TargetType::___TypeRegistration::addField(this);                 \
    }                                                                       \
    constexpr const char* name() const override {                           \
        return #name_;                                                      \
    }                                                                       \
    const Il2CppType* type() const override {                               \
        ::il2cpp_functions::Init();                                         \
        return ::il2cpp_functions::class_get_type(                          \
            il2cpp_utils::GetClassFromName(namezpace_, klass_)              \
        );                                                                  \
    }                                                                       \
    constexpr uint16_t fieldAttributes() const override {                   \
        return FIELD_ATTRIBUTE_PUBLIC;                                      \
    }                                                                       \
    constexpr size_t size() const override {                                \
        return sizeof(type_);                                               \
    }                                                                       \
    int32_t offset() const override {                                       \
        return offsetof(___TargetType, name_);                              \
    }                                                                       \
};                                                                          \
static inline ___FieldRegistrator_##name_ ___##name_##_FieldRegistrator;    \
public:                                                                     \
type_ name_

DECLARE_CLASS_CODEGEN(BSML, Key, Il2CppObject,
    DECLARE_INSTANCE_FIELD(StringW, name);
    DECLARE_INSTANCE_FIELD(StringW, value);
    DECLARE_INSTANCE_FIELD(StringW, shifted);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, button);
    DECLARE_INSTANCE_FIELD_TYPENAME(Keyboard*, kb, "BSML", "Keyboard");

    DECLARE_DEFAULT_CTOR();
    public:
        void OnClick();
        bool KeyAction();
        bool Enter();

        Key* Set(StringW value);
        static Key* construct();
        static Key* construct(Keyboard* kb, UnityEngine::Vector2 position, StringW text, float width, float height, UnityEngine::Color color);

        std::function<void(Key*)> keyAction = nullptr;
)