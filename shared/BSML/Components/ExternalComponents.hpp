#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Component.hpp"

DECLARE_CLASS_CORDL(BSML, ExternalComponents, UnityEngine::MonoBehaviour,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(ListWrapper<UnityEngine::Component>, components);
    );
    FIELD_ACCESSOR(components);

    DECLARE_INSTANCE_METHOD(void, Add, UnityEngine::Component component);
    DECLARE_CTOR(ctor);

    public:
        UnityEngine::Component GetByType(System::Type type) const;
        UnityEngine::Component GetByType(Il2CppReflectionType* type) const;
        template<typename T>
        requires(std::is_convertible_v<T, UnityEngine::Component>)
        T Get() const {
            return T(GetByType(csTypeOf(T)).convert());
        }
);
