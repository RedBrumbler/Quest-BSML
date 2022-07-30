#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

#ifndef DECLARE_INSTANCE_FIELD_TYPENAME
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
#endif

namespace BSML {
    class TabSelector;
}

DECLARE_CLASS_CODEGEN(BSML, Tab, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_FIELD_TYPENAME(TabSelector*, selector, "BSML", "TabSelector");
    DECLARE_INSTANCE_FIELD(StringW, tabName);
    DECLARE_INSTANCE_FIELD(StringW, tabKey);
    DECLARE_INSTANCE_FIELD(bool, isVisible);

    DECLARE_INSTANCE_METHOD(bool, get_isVisible);
    DECLARE_INSTANCE_METHOD(void, set_isVisible, bool value);

    DECLARE_INSTANCE_METHOD(StringW, get_tabName);
    DECLARE_INSTANCE_METHOD(void, set_tabName, StringW value);

    DECLARE_INSTANCE_METHOD(StringW, get_tabKey);
    DECLARE_INSTANCE_METHOD(void, set_tabKey, StringW value);

    DECLARE_CTOR(ctor);
)