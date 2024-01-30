#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/MeshRenderer.hpp"

#include "UnityEngine/EventSystems/IPointerEnterHandler.hpp"
#include "UnityEngine/EventSystems/IPointerExitHandler.hpp"
#include "UnityEngine/EventSystems/PointerEventData.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES_EXPORT(BSML, FloatingScreenHandle, UnityEngine::MonoBehaviour, std::vector<Il2CppClass*>({classof(::UnityEngine::EventSystems::IPointerEnterHandler*), classof(::UnityEngine::EventSystems::IPointerExitHandler*)}),
    DECLARE_INSTANCE_FIELD(UnityEngine::Material*, originalMaterial);
    DECLARE_INSTANCE_FIELD(UnityEngine::MeshRenderer*, renderer);

    DECLARE_INSTANCE_METHOD(void, Awake);
    DECLARE_OVERRIDE_METHOD_MATCH(void, OnPointerEnter, &::UnityEngine::EventSystems::IPointerEnterHandler::OnPointerEnter, UnityEngine::EventSystems::PointerEventData* eventData);
    DECLARE_OVERRIDE_METHOD_MATCH(void, OnPointerExit, &::UnityEngine::EventSystems::IPointerExitHandler::OnPointerExit, UnityEngine::EventSystems::PointerEventData* eventData);

    private:
        static SafePtrUnity<UnityEngine::Material> hoverMaterial;
        static UnityEngine::Material* get_hoverMaterial();
)
