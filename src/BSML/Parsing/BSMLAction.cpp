#include "BSML/Parsing/BSMLAction.hpp"

extern void collect_minfos(Il2CppClass* klass, std::vector<const MethodInfo*>& minfos);

namespace BSML {
    BSMLAction::BSMLAction(bs_hook::Il2CppWrapperType host, const MethodInfo* methodInfo) : host(host), methodInfo(methodInfo) {}

    BSMLAction* BSMLAction::MakeAction(bs_hook::Il2CppWrapperType host, std::string methodName, int argc) {
        const MethodInfo* minfo = nullptr;
        auto klass = il2cpp_functions::object_get_class(host);
        while (klass && !minfo) {
            minfo = il2cpp_functions::class_get_method_from_name(klass, methodName.c_str(), argc);
            klass = klass->parent;
        }

        return new BSMLAction(host, minfo);
    }

    std::map<std::string, BSMLAction*> BSMLAction::MakeActions(bs_hook::Il2CppWrapperType host) {
        std::vector<const MethodInfo*> minfos;
        collect_minfos(host->klass, minfos);

        std::map<std::string, BSMLAction*> actions;
        for (auto minfo : minfos) {
            actions.insert({minfo->name, new BSMLAction(host, minfo)});
        }

        return actions;
    }
}
