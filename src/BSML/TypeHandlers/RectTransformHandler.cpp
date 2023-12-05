#include "BSML/TypeHandlers/RectTransformHandler.hpp"
#include "Helpers/utilities.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/HoverHint.hpp"
#include "Helpers/getters.hpp"

void AddHoverHint(UnityEngine::RectTransform rectTransform, const std::string& text) {
    auto hoverHint = rectTransform->GetComponent<HMUI::HoverHint>();
    if (!hoverHint) {
        hoverHint = rectTransform.gameObject.AddComponent<HMUI::HoverHint>();
    }
    hoverHint.text = text;
    hoverHint.hoverHintController = BSML::Helpers::GetHoverHintController();
}

// for now, because I wanna have the option later
void AddHoverHintKey(UnityEngine::RectTransform rectTransform, const std::string& key) {
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
            {"anchorMinX",      [](auto component, auto value){ component.anchorMin = UnityEngine::Vector2(value, component.anchorMin.y); }},
            {"anchorMinY",      [](auto component, auto value){ component.anchorMin = UnityEngine::Vector2(component.anchorMin.x, value); }},
            {"anchorMaxX",      [](auto component, auto value){ component.anchorMax = UnityEngine::Vector2(value, component.anchorMax.y); }},
            {"anchorMaxY",      [](auto component, auto value){ component.anchorMax = UnityEngine::Vector2(component.anchorMax.x, value); }},
            {"anchorPosX",      [](auto component, auto value){ component.anchoredPosition = UnityEngine::Vector2(value, component.anchoredPosition.y); }},
            {"anchorPosY",      [](auto component, auto value){ component.anchoredPosition = UnityEngine::Vector2(component.anchoredPosition.x, value); }},
            {"sizeDeltaX",      [](auto component, auto value){ component.sizeDelta = UnityEngine::Vector2(value, component.sizeDelta.y); }},
            {"sizeDeltaY",      [](auto component, auto value){ component.sizeDelta = UnityEngine::Vector2(component.sizeDelta.x, value); }},
            {"pivotX",          [](auto component, auto value){ component.pivot = UnityEngine::Vector2(value, component.pivot.y); }},
            {"pivotY",          [](auto component, auto value){ component.pivot = UnityEngine::Vector2(component.pivot.x, value); }},
            {"hoverHint",       [](auto component, auto value){ AddHoverHint(component, value); }},
            {"hoverHintKey",    [](auto component, auto value){ AddHoverHintKey(component, value); }},
            {"active",          [](auto component, auto value){ component.gameObject.SetActive(value); }}
        };
    }
}
