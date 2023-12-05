#pragma once

#include "../../Helpers/delegates.hpp"
#include <string>
#include <map>

namespace BSML {
    class BSMLAction {
        public:
            BSMLAction(bs_hook::Il2CppWrapperType host, const MethodInfo* methodInfo);

            bs_hook::Il2CppWrapperType host;
            const MethodInfo* methodInfo;

            template<typename T = bs_hook::Il2CppWrapperType, typename... Targs>
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

            static BSMLAction* MakeAction(bs_hook::Il2CppWrapperType host, std::string methodName, int argc = 0);
            static std::map<std::string, BSMLAction*> MakeActions(bs_hook::Il2CppWrapperType host);
    };
}
