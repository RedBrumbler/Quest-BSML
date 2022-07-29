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
        auto itr = std::find(get_typeHandlers().begin(), get_typeHandlers().end(), typeHandler);
        if (itr == get_typeHandlers().end()) {
            INFO("Registered type handler");
            get_typeHandlers().emplace_back(typeHandler);
        }
        INFO("type handler count: {}", get_typeHandlers().size());
    }

    void TypeHandlerBase::UnRegisterTypeHandler(TypeHandlerBase* typeHandler) {
        auto itr = std::find(get_typeHandlers().begin(), get_typeHandlers().end(), typeHandler);
        if (itr != get_typeHandlers().end()) {
            INFO("UnRegistered type handler");
            get_typeHandlers().erase(itr, itr++);
        }
        INFO("type handler count: {}", get_typeHandlers().size());
    }
}