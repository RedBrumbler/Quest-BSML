#include "BSML/TypeHandlers/TypeHandler.hpp"
#include "Helpers/utilities.hpp"

namespace BSML {
    
    std::vector<TypeHandlerBase*>& TypeHandlerBase::get_typeHandlers() {
        static std::vector<TypeHandlerBase*> typeHandlers = {};
        return typeHandlers;
    }

    const TypeHandlerBase::PropMap& TypeHandlerBase::get_cachedProps() {
        if (cachedProps.empty())
            cachedProps = get_props();
        return cachedProps;
    }

    void TypeHandlerBase::RegisterTypeHandler(TypeHandlerBase* typeHandler) {
        auto& typeHandlers = get_typeHandlers();
        auto itr = std::find(typeHandlers.begin(), typeHandlers.end(), typeHandler);
        if (itr == typeHandlers.end()) {
            INFO("Registered type handler");
            typeHandlers.emplace_back(typeHandler);
        }
        std::sort(typeHandlers.begin(), typeHandlers.end(), [](auto lhs, auto rhs) { return lhs->get_priority() < rhs->get_priority(); });
        INFO("type handler count: {}", typeHandlers.size());
    }

    void TypeHandlerBase::UnRegisterTypeHandler(TypeHandlerBase* typeHandler) {
        auto& typeHandlers = get_typeHandlers();
        auto itr = std::find(typeHandlers.begin(), typeHandlers.end(), typeHandler);
        if (itr != typeHandlers.end()) {
            INFO("UnRegistered type handler");
            typeHandlers.erase(itr, itr++);
        }
        INFO("type handler count: {}", typeHandlers.size());
    }
}