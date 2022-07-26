#pragma once

#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(BSML, GenericSettingWrapper, Il2CppObject,
    DECLARE_INSTANCE_FIELD(Il2CppObject*, host);
    DECLARE_INSTANCE_FIELD(bool, applyOnChange); /* default: true */
    DECLARE_CTOR(ctor);

    public:
        FieldInfo* valueInfo;
        const MethodInfo* setterInfo;
        const MethodInfo* getterInfo;
        const MethodInfo* onChangeInfo;
        
        template<typename T>
        void SetValue(T value) {
            if (valueInfo) {
                SetField<T>(value);
            } else if (setterInfo) {
                SetProperty<T>(value);
            }
        }

        template<typename T>
        void SetField(T value) {
            il2cpp_utils::SetFieldValue(host, valueInfo, value);
        }

        template<typename T>
        void SetProperty(T value) {
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

        template<typename T>
        std::optional<T> GetValueOpt() {
            if (valueInfo) {
                return GetFieldOpt<T>();
            }
            if (getterInfo) {
                return GetPropertyOpt<T>();
            }
            return std::nullopt;
        }

        template<typename T>
        std::optional<T> GetFieldOpt() {
            return valueInfo ? il2cpp_utils::GetFieldValue<T>(host, valueInfo) : std::nullopt;
        }

        template<typename T>
        std::optional<T> GetPropertyOpt()  {
            return getterInfo ? il2cpp_utils::RunMethod<T>(host, getterInfo) : std::nullopt;
        }

        void OnChange() {
            if (onChangeInfo) il2cpp_utils::RunMethod(host, onChangeInfo);
        }

        template<typename T>
        void OnChange(T value) {
            // ìf the given onchange info only has 1 parameter (implicit this ptr) we just use the OnChange(void) method
            if (onChangeInfo && onChangeInfo->parameters_count < 1) {
                OnChange();
                return;
            } else if (onChangeInfo){
                il2cpp_utils::RunMethod(host, onChangeInfo, value);
            }
        }
)