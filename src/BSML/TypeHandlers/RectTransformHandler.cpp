#include "BSML/TypeHandlers/RectTransformHandler.hpp"
#include "Helpers/utilities.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/HoverHint.hpp"
#include "Helpers/getters.hpp"

void AddHoverHint(UnityEngine::RectTransform* rectTransform, const std::string& text) {
    auto hoverHint = rectTransform->GetComponent<HMUI::HoverHint*>();
    if (!hoverHint) {
        hoverHint = rectTransform->get_gameObject()->AddComponent<HMUI::HoverHint*>();
    }
    hoverHint->set_text(text);
    hoverHint->hoverHintController = BSML::Helpers::GetHoverHintController();
}

// for now, because I wanna have the option later
void AddHoverHintKey(UnityEngine::RectTransform* rectTransform, const std::string& key) {
    AddHoverHint(rectTransform, key);
}

namespace BSML {
    static RectTransformHandler rectTransformHandler{};

    RectTransformHandler::Base::PropMap RectTransformHandler::get_props() const {
        return {
            {"anchorMinX", {"anchor-min-x"}},
            {"anchorMinY", {"anchor-min-y"}},
            {"anchorMaxX", {"anchor-max-x"}},
            {"anchorMaxY", {"anchor-max-y"}},
            {"anchorPosX", {"anchor-pos-x"}},
            {"anchorPosY", {"anchor-pos-y"}},
            {"sizeDeltaX", {"size-delta-x"}},
            {"sizeDeltaY", {"size-delta-y"}},
            {"pivotX", {"pivot-x"}},
            {"pivotY", {"pivot-y"}},
            {"hoverHint", {"hover-hint"}},
            {"hoverHintKey", {"hover-hint-key"}},
            {"active", {"active"}}
        };
    }

    RectTransformHandler::Base::SetterMap RectTransformHandler::get_setters() const {
        return {
            {"anchorMinX",      [](auto component, auto value){ component->set_anchorMin(UnityEngine::Vector2(value, component->get_anchorMin().y)); }},
            {"anchorMinY",      [](auto component, auto value){ component->set_anchorMin(UnityEngine::Vector2(component->get_anchorMin().x, value)); }},
            {"anchorMaxX",      [](auto component, auto value){ component->set_anchorMax(UnityEngine::Vector2(value, component->get_anchorMax().y)); }},
            {"anchorMaxY",      [](auto component, auto value){ component->set_anchorMax(UnityEngine::Vector2(component->get_anchorMax().x, value)); }},
            {"anchorPosX",      [](auto component, auto value){ component->set_anchoredPosition(UnityEngine::Vector2(value, component->get_anchoredPosition().y)); }},
            {"anchorPosY",      [](auto component, auto value){ component->set_anchoredPosition(UnityEngine::Vector2(component->get_anchoredPosition().x, value)); }},
            {"sizeDeltaX",      [](auto component, auto value){ component->set_sizeDelta(UnityEngine::Vector2(value, component->get_sizeDelta().y)); }},
            {"sizeDeltaY",      [](auto component, auto value){ component->set_sizeDelta(UnityEngine::Vector2(component->get_sizeDelta().x, value)); }},
            {"pivotX",          [](auto component, auto value){ component->set_pivot(UnityEngine::Vector2(value, component->get_pivot().y)); }},
            {"pivotY",          [](auto component, auto value){ component->set_pivot(UnityEngine::Vector2(component->get_pivot().x, value)); }},
            {"hoverHint",       [](auto component, auto value){ AddHoverHint(component, value); }},
            {"hoverHintKey",    [](auto component, auto value){ AddHoverHintKey(component, value); }},
            {"active",          [](auto component, auto value){ component->get_gameObject()->SetActive(value); }}
        };
    }
}