#pragma once

#include "custom-types/shared/macros.hpp"
#include "logging.hpp"

DECLARE_CLASS_CODEGEN(BSML, GenericSettingWrapper, Il2CppObject,
    DECLARE_INSTANCE_FIELD(Il2CppObject*, host);
    DECLARE_INSTANCE_FIELD(bool, applyOnChange); /* default: true */
    DECLARE_CTOR(ctor);

    public:
        FieldInfo* valueInfo = nullptr;
        const MethodInfo* setterInfo = nullptr;
        const MethodInfo* getterInfo = nullptr;
        const MethodInfo* onChangeInfo = nullptr;
        
        template<typename T>
        void SetValue(const T& value) {
            if (valueInfo) {
                SetField<T>(value);
            } else if (setterInfo) {
                SetProperty<T>(value);
            }
        }

        template<typename T>
        void SetField(const T& value) {
            il2cpp_utils::SetFieldValue(host, valueInfo, value);
        }

        template<typename T>
        void SetProperty(const T& value) {
            il2cpp_utils::RunMethod(host, setterInfo, value);
        }

        template<typename T>
        requires(std::is_default_constructible_v<T>)
        T GetValue() {
            if (valueInfo) {
                return GetField<T>();
            }
            if (getterInfo) {
                return GetProperty<T>();
            }

            return T{};
        }

        template<typename T>
        requires(std::is_default_constructible_v<T>)
        T GetField() {
            return valueInfo ? il2cpp_utils::GetFieldValue<T>(host, valueInfo).value_or(T{}) : T{};
        }

        template<typename T>
        requires(std::is_default_constructible_v<T>)
        T GetProperty()  {
            return getterInfo ? il2cpp_utils::RunMethod<T>(host, getterInfo).value_or(T{}) : T{};
        }

        void OnChange() {
            if (onChangeInfo) il2cpp_utils::RunMethod(host, onChangeInfo);
        }

        template<typename T>
        void OnChange(const T& value) {
            // ìf the given onchange info only has 1 parameter (implicit this ptr) we just use the OnChange(void) method
            if (onChangeInfo && onChangeInfo->parameters_count < 1) {
                OnChange();
                return;
            }

            if (onChangeInfo) il2cpp_utils::RunMethod(host, onChangeInfo, value);
        }
)