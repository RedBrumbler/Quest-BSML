#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/MeshRenderer.hpp"

#include "UnityEngine/EventSystems/IPointerEnterHandler.hpp"
#include "UnityEngine/EventSystems/IPointerExitHandler.hpp"
#include "UnityEngine/EventSystems/PointerEventData.hpp"

#define INTERFACES { classof(::UnityEngine::EventSystems::IPointerEnterHandler*), classof(::UnityEngine::EventSystems::IPointerExitHandler*) }

___DECLARE_TYPE_WRAPPER_INHERITANCE(BSML, FloatingScreenHandle, Il2CppTypeEnum::IL2CPP_TYPE_CLASS, UnityEngine::MonoBehaviour, "BSML", INTERFACES, 0, nullptr,
    DECLARE_INSTANCE_FIELD(UnityEngine::Material*, originalMaterial);
    DECLARE_INSTANCE_FIELD(UnityEngine::MeshRenderer*, renderer);

    DECLARE_INSTANCE_METHOD(void, Awake);
    DECLARE_OVERRIDE_METHOD(void, OnPointerEnter, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::UnityEngine::EventSystems::IPointerEnterHandler::OnPointerEnter>::get(), UnityEngine::EventSystems::PointerEventData* eventData);
    DECLARE_OVERRIDE_METHOD(void, OnPointerExit, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::UnityEngine::EventSystems::IPointerExitHandler::OnPointerExit>::get(), UnityEngine::EventSystems::PointerEventData* eventData);

    private:
        static SafePtrUnity<UnityEngine::Material> hoverMaterial;
        static UnityEngine::Material* get_hoverMaterial();
)

#undef INTERFACES