#pragma once

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include <map>

namespace BSML {
    struct BSMLValue {
        std::string name;
        Il2CppObject* host;

        FieldInfo* fieldInfo;
        const MethodInfo* setterInfo;
        const MethodInfo* getterInfo;

        virtual void SetValue(Il2CppObject* val);
        virtual Il2CppObject* GetValue();

        template<typename T>
        requires(!std::is_same_v<Il2CppObject*, T>)
        void SetValue(T val) {
            if (fieldInfo) {
                il2cpp_functions::field_set_value(host, fieldInfo, &val);
            } else if (setterInfo) {
                il2cpp_utils::RunMethod(host, setterInfo, val);
            }
        }

        template<typename T>
        requires(std::is_default_constructible_v<T> && !std::is_same_v<Il2CppObject*, T>)
        T GetValue() {
            if (fieldInfo) {
                T val;
                il2cpp_functions::field_get_value(host, fieldInfo, &val);
                return val;
            } else if (getterInfo) {
                return il2cpp_utils::RunMethod<T>(host, getterInfo).value_or(T());
            }
            return T{};
        }

        template<typename T>
        requires(!std::is_same_v<Il2CppObject*, T>)
        std::optional<T> GetValueOpt() {
            if (fieldInfo) {
                return il2cpp_utils::GetFieldValue<T>(host, fieldInfo);
            } else if (getterInfo) {
                return il2cpp_utils::RunMethod<T>(host, getterInfo);
            }
            return std::nullopt;
        }

        static std::map<std::string, BSMLValue*> MakeValues(Il2CppObject* host);
    };
}