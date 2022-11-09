#include "BSML/FloatingScreen/FloatingScreenHandle.hpp"

#include "UnityEngine/Shader.hpp"

DEFINE_TYPE(BSML, FloatingScreenHandle);

namespace BSML {
    SafePtrUnity<UnityEngine::Material> FloatingScreenHandle::hoverMaterial;
    UnityEngine::Material* FloatingScreenHandle::get_hoverMaterial() {
        if (!hoverMaterial) {
            auto shader = UnityEngine::Shader::Find("Hidden/Internal-DepthNormalsTexture");
            hoverMaterial = UnityEngine::Material::New_ctor(shader);
        }

        return hoverMaterial.ptr();
    }


    void FloatingScreenHandle::Awake() {
        renderer = GetComponent<UnityEngine::MeshRenderer*>();
        originalMaterial = renderer->get_material();
    }

    void FloatingScreenHandle::OnPointerEnter(UnityEngine::EventSystems::PointerEventData* eventData) {
        renderer->set_material(get_hoverMaterial());
    }

    void FloatingScreenHandle::OnPointerExit(UnityEngine::EventSystems::PointerEventData* eventData) {
        renderer->set_material(originalMaterial);
    }
}