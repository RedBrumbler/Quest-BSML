#pragma once

#include "custom-types/shared/macros.hpp"
#include "logging.hpp"

namespace BSML {
    enum class SetterType {
            None = 0,
            Field = 1,
            Property = 2,
            Method = 4,
            All = Field | Property | Method,
    };

    int operator& (BSML::SetterType lhs, BSML::SetterType rhs);
    BSML::SetterType operator| (BSML::SetterType lhs, BSML::SetterType rhs);
    BSML::SetterType& operator|= (BSML::SetterType& self, BSML::SetterType rhs);
}

DECLARE_CLASS_CODEGEN(BSML, ValueWrapper, Il2CppObject,
    DECLARE_INSTANCE_FIELD(Il2CppObject*, host);
    DECLARE_INSTANCE_FIELD(int, setterType);

    DECLARE_DEFAULT_CTOR();

    public:
        /* for some reason fieldInfo can't be const 😢 */
        FieldInfo* fieldInfo = nullptr;
        const MethodInfo* getterInfo = nullptr;
        const MethodInfo* setterInfo = nullptr;
        const MethodInfo* methodInfo = nullptr;

        SetterType get_setterType() const;
        void set_setterType(int value);
        void set_setterType(SetterType value);

        template<typename T>
        void SetValue(const T& value) {
            if (get_setterType() & SetterType::Field) {
                SetField<T>(value);
            }
            if (get_setterType() & SetterType::Property) {
                SetProperty<T>(value);
            }
            if (get_setterType() & SetterType::Method) {
                RunMethod();
            }
        }

        template<typename T>
        void SetField(const T& value) {
            if (fieldInfo) il2cpp_utils::SetFieldValue(host, fieldInfo, value);
        }

        template<typename T>
        void SetProperty(const T& value) {
            if (setterInfo) il2cpp_utils::RunMethod(host, setterInfo, value);
        }

        void RunMethod() {
            if (methodInfo) il2cpp_utils::RunMethod(host, methodInfo);
        }

        template<typename T>
        requires(std::is_default_constructible_v<T>)
        T GetValue() {
            if (get_setterType() & SetterType::Field) {
                return GetField<T>();
            }
            if (get_setterType() & SetterType::Property) {
                return GetProperty<T>();
            }

            return T{};
        }

        template<typename T>
        requires(std::is_default_constructible_v<T>)
        T GetField() {
            return fieldInfo ? il2cpp_utils::GetFieldValue<T>(host, fieldInfo).value_or(T{}) : T{};
        }

        template<typename T>
        requires(std::is_default_constructible_v<T>)
        T GetProperty()  {
            return getterInfo ? il2cpp_utils::RunMethod<T>(host, getterInfo).value_or(T{}) : T{};
        }
)