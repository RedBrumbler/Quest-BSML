#include "BSML/Components/ExternalComponents.hpp"

DEFINE_TYPE(BSML, ExternalComponents);

namespace BSML {
    void ExternalComponents::ctor() {
        components = List<UnityEngine::Component*>::New_ctor();
    }

    void ExternalComponents::Add(UnityEngine::Component* component) {
        components->Add(component);
    }

    UnityEngine::Component* ExternalComponents::GetByType(System::Type* type) const {
        return GetByType(reinterpret_cast<Il2CppReflectionType*>(type));
    }
    
    UnityEngine::Component* ExternalComponents::GetByType(Il2CppReflectionType* type) const {
        if (!type) {
            return nullptr;
        }
        auto klass = il2cpp_functions::class_from_system_type(type);
        for (auto component : components) {
            if (il2cpp_functions::class_is_assignable_from(klass, component->klass)) {
                return component;
            }
        }

        return nullptr;
    }
}