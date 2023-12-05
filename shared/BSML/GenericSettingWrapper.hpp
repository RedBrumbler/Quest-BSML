#pragma once

#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CORDL(BSML, GenericSettingWrapper, bs_hook::Il2CppWrapperType,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(bs_hook::Il2CppWrapperType, host);
        DECLARE_INSTANCE_FIELD(bs_hook::Il2CppWrapperType, onChangeHost);
        DECLARE_INSTANCE_FIELD(bool, applyOnChange); /* default: true */

    public:
        FieldInfo* valueInfo;
        const MethodInfo* setterInfo;
        const MethodInfo* getterInfo;
        const MethodInfo* onChangeInfo;
    );

    FIELD_ACCESSOR(host);
    FIELD_ACCESSOR(onChangeHost);
    FIELD_ACCESSOR(applyOnChange);
    FIELD_ACCESSOR(valueInfo);
    FIELD_ACCESSOR(setterInfo);
    FIELD_ACCESSOR(getterInfo);
    FIELD_ACCESSOR(onChangeInfo);

    DECLARE_CTOR(ctor);

    public:

        bs_hook::Il2CppWrapperType get_onChangeHost();
        bs_hook::Il2CppWrapperType get_host();

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
            il2cpp_utils::SetFieldValue(get_host(), valueInfo, value);
        }

        template<typename T>
        void SetProperty(T value) {
            il2cpp_utils::RunMethod(get_host(), setterInfo, value);
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
            return valueInfo ? il2cpp_utils::GetFieldValue<T>(get_host(), valueInfo).value_or(T{}) : T{};
        }

        template<typename T>
        requires(std::is_default_constructible_v<T>)
        T GetProperty()  {
            return getterInfo ? il2cpp_utils::RunMethod<T>(get_host(), getterInfo).value_or(T{}) : T{};
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
            return valueInfo ? il2cpp_utils::GetFieldValue<T>(get_host(), valueInfo) : std::nullopt;
        }

        template<typename T>
        std::optional<T> GetPropertyOpt()  {
            return getterInfo ? il2cpp_utils::RunMethod<T>(get_host(), getterInfo) : std::nullopt;
        }

        void OnChange() {
            if (onChangeInfo) il2cpp_utils::RunMethod(get_onChangeHost(), onChangeInfo);
        }

        template<typename T>
        void OnChange(T value) {
            // ìf the given onchange info only has 1 parameter (implicit this ptr) we just use the OnChange(void) method
            if (onChangeInfo && onChangeInfo->parameters_count < 1) {
                OnChange();
                return;
            } else if (onChangeInfo){
                il2cpp_utils::RunMethod(get_onChangeHost(), onChangeInfo, value);
            }
        }
)
