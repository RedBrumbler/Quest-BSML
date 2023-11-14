#include "BSML/Components/Clickable.hpp"

DEFINE_TYPE(BSML, Clickable);

namespace BSML {
    void Clickable::ctor() {
        INVOKE_CTOR();
        INVOKE_BASE_CTOR(classof(HMUI::Touchable*));
    }

    void Clickable::OnPointerClick(UnityEngine::EventSystems::PointerEventData* eventData) {
        auto onClick = this->onClick;
        onClick.invoke();
    }

    void Clickable::OnPointerEnter(UnityEngine::EventSystems::PointerEventData* eventData) {
        auto onEnter = this->onEnter;
        onEnter.invoke();
    }

    void Clickable::OnPointerExit(UnityEngine::EventSystems::PointerEventData* eventData) {
        auto onExit = this->onExit;
        onExit.invoke();
    }
}
