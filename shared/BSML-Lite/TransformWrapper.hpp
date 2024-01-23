#pragma once

#include "beatsaber-hook/shared/utils/typedefs.h"
#include "beatsaber-hook/shared/utils/type-concepts.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Component.hpp"
#include "UnityEngine/GameObject.hpp"

namespace BSML::Lite {
    /// @brief A wrapper for transforms, components and gameobjects to automatically be converted into a transform
    struct TransformWrapper {
        TransformWrapper(UnityEngine::RectTransform* transform) noexcept : transform(transform) {}
        TransformWrapper(UnityEngine::Transform* transform) noexcept : transform(transform) {}
        TransformWrapper(UnityEngine::Component* comp) : TransformWrapper(comp->get_transform()) {}
        TransformWrapper(UnityEngine::GameObject* go) : TransformWrapper(go->get_transform()) {}

        // il2cpp wrapper type
        explicit TransformWrapper(void* i) : transform(static_cast<UnityEngine::Transform*>(i)) {}
        constexpr inline void* convert() const noexcept { return const_cast<void*>(static_cast<const void*>(transform)); }

        UnityEngine::Transform* operator->() const noexcept { return transform; }
        operator UnityEngine::Transform*() const noexcept { return transform; }
        UnityEngine::Transform* transform;
    };
}
MARK_REF_T(BSML::Lite::TransformWrapper);

template<>
struct ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<BSML::Lite::TransformWrapper> {
    static inline Il2CppClass* get() {
        return classof(UnityEngine::Transform*);
    }
};
static_assert(sizeof(BSML::Lite::TransformWrapper) == sizeof(UnityEngine::Transform*));
