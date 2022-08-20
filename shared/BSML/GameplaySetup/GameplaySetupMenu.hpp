#pragma once

#include "custom-types/shared/macros.hpp"
#include "../Components/Tab.hpp"
#include "MenuType.hpp"
#include <string>

#define DECLARE_INSTANCE_CPP_ENUM_FIELD(type_, enumType_, name_) \
static_assert(sizeof(type_) == sizeof(enumType_), "size mismatch"); \
private: \
struct ___FieldRegistrator_##name_ : ::custom_types::FieldRegistrator { \
    ___FieldRegistrator_##name_() { \
        ___TargetType::___TypeRegistration::addField(this); \
    } \
    constexpr const char* name() const override { \
        return #name_; \
    } \
    const Il2CppType* type() const override { \
        ::il2cpp_functions::Init(); \
        return ::il2cpp_functions::class_get_type(::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<type_>::get()); \
    } \
    constexpr uint16_t fieldAttributes() const override { \
        return FIELD_ATTRIBUTE_PUBLIC; \
    } \
    constexpr size_t size() const override { \
        return sizeof(type_); \
    } \
    int32_t offset() const override { \
        return offsetof(___TargetType, name_); \
    } \
}; \
static inline ___FieldRegistrator_##name_ ___##name_##_FieldRegistrator; \
public: \
enumType_ name_

DECLARE_CLASS_CODEGEN(BSML, GameplaySetupMenu, Il2CppObject,
    DECLARE_INSTANCE_FIELD(StringW, name);
    DECLARE_INSTANCE_FIELD(StringW, content_key);
    DECLARE_INSTANCE_FIELD(Il2CppObject*, host);
    DECLARE_INSTANCE_CPP_ENUM_FIELD(int, MenuType, menuType);
    DECLARE_INSTANCE_FIELD(Tab*, tab);

    DECLARE_INSTANCE_METHOD(bool, get_visible);
    DECLARE_INSTANCE_METHOD(void, set_visible, bool value);

    DECLARE_INSTANCE_METHOD(void, Setup);
    DECLARE_INSTANCE_METHOD(void, PostParse);
    DECLARE_INSTANCE_METHOD(void, SetVisible, bool isVisible);

    public:
        static GameplaySetupMenu* Make_new(std::string_view name, std::string_view content_key, Il2CppObject* host, BSML::MenuType menuType = BSML::MenuType::All);
        bool get_content(std::string_view& content);

        bool IsMenuType(BSML::MenuType toCheck);
    
        DECLARE_DEFAULT_CTOR();
)