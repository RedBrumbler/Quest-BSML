#pragma once

#include "beatsaber-hook/shared/utils/typedefs.h"
#include "beatsaber-hook/shared/utils/type-concepts.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Component.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Transform.hpp"

namespace BSML::Lite {
    /// @brief A wrapper for transforms, components and gameobjects to automatically be converted into a gameObject
    struct GameObjectWrapper {
        GameObjectWrapper(UnityEngine::GameObject* gameObject) noexcept : gameObject(gameObject) {}
        GameObjectWrapper(UnityEngine::Component* comp) : GameObjectWrapper(comp->get_gameObject()) {}
        GameObjectWrapper(UnityEngine::RectTransform* transform) : GameObjectWrapper(transform->get_gameObject()) {}
        GameObjectWrapper(UnityEngine::Transform* transform) : GameObjectWrapper(transform->get_gameObject()) {}

        // il2cpp wrapper type
        explicit GameObjectWrapper(void* i) : gameObject(static_cast<UnityEngine::GameObject*>(i)) {}
        constexpr inline void* convert() const noexcept { return const_cast<void*>(static_cast<const void*>(gameObject)); }

        UnityEngine::GameObject* operator->() const noexcept { return const_cast<UnityEngine::GameObject*>(gameObject); }
        operator UnityEngine::GameObject*() const noexcept { return const_cast<UnityEngine::GameObject*>(gameObject); }
        UnityEngine::GameObject* gameObject;
    };
}
MARK_REF_T(BSML::Lite::GameObjectWrapper);

template<>
struct ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<BSML::Lite::GameObjectWrapper> {
    static inline Il2CppClass* get() {
        return classof(UnityEngine::GameObject*);
    }
};
static_assert(sizeof(BSML::Lite::GameObjectWrapper) == sizeof(UnityEngine::GameObject*));
