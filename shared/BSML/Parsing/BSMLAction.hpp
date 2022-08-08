#pragma once

#include "../../Helpers/delegates.hpp"
#include <string>
#include <map>

namespace BSML {
    class BSMLAction {
        public:
            BSMLAction(Il2CppObject* host, const MethodInfo* methodInfo);

            Il2CppObject* host;
            const MethodInfo* methodInfo;

            template<typename T = Il2CppObject*, typename... Targs>
            std::optional<T> Invoke(Targs&&... args) const {
                return il2cpp_utils::RunMethod<T>(host, methodInfo, args...);
            }

            template<typename... Targs>
            std::function<void(Targs...)> GetFunction() const {
                return [host = this->host, methodInfo = this->methodInfo](Targs... args) {
                    il2cpp_utils::RunMethod(host, methodInfo, args...);
                };
            }

            template<typename... Targs>
            auto GetSystemAction() const {
                return BSML::MakeSystemAction<Targs...>(host, methodInfo);
            }

            template<typename... Targs>
            auto GetUnityAction() const {
                return BSML::MakeUnityAction<Targs...>(host, methodInfo);
            };

            static BSMLAction* MakeAction(Il2CppObject* host, std::string methodName, int argc = 0);
            static std::map<std::string, BSMLAction*> MakeActions(Il2CppObject* host);
    };
}