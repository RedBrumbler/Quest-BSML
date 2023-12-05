#include "BSML/Components/ClickableText.hpp"
#include "logging.hpp"

#include "VRUIControls/VRPointer.hpp"

DEFINE_TYPE(BSML, ClickableText);

namespace BSML {
    void ClickableText::ctor() {
        INVOKE_CTOR();

        isHighlighted = false;
        highlightColor = UnityEngine::Color(0.60f, 0.80f, 1.0f, 1.0f);
        defaultColor = UnityEngine::Color(1.0f, 1.0f, 1.0f, 1.0f);

        onEnter = nullptr;
        onExit = nullptr;

        buttonClickedSignal = nullptr;
        hapticFeedbackController = nullptr;
        hapticFeedbackPresetSO = nullptr;

        INVOKE_BASE_CTOR(classof(HMUI::CurvedTextMeshPro));
    }

    void ClickableText::UpdateHighlight() {
        color = isHighlighted ? highlightColor : defaultColor;
    }

    void ClickableText::OnPointerClick(UnityEngine::EventSystems::PointerEventData eventData) {
        INFO("Click");
        if (buttonClickedSignal) buttonClickedSignal.Raise();
        isHighlighted = false;
        if (onClick.size() > 0) onClick.invoke();
    }

    void ClickableText::OnPointerEnter(UnityEngine::EventSystems::PointerEventData eventData) {
        INFO("Enter");
        isHighlighted = true;
        if (onEnter) onEnter();
        Vibrate(!VRUIControls::VRPointer::_get__lastControllerUsedWasRight());
    }

    void ClickableText::OnPointerExit(UnityEngine::EventSystems::PointerEventData eventData) {
        INFO("Exit");
        isHighlighted = false;
        if (onExit) onExit();
    }

    void ClickableText::Vibrate(bool left)
    {
        UnityEngine::XR::XRNode node = left ? UnityEngine::XR::XRNode::LeftHand : UnityEngine::XR::XRNode::RightHand;
        if (hapticFeedbackController && hapticFeedbackPresetSO) hapticFeedbackController.PlayHapticFeedback(node, hapticFeedbackPresetSO);
    }

    void ClickableText::set_highlightColor(UnityEngine::Color color) {
        highlightColor = color;
        UpdateHighlight();
    }

    UnityEngine::Color ClickableText::get_highlightColor() {
        return highlightColor;
    }

    void ClickableText::set_defaultColor(UnityEngine::Color color) {
        _defaultColor = color;
        UpdateHighlight();
    }

    UnityEngine::Color ClickableText::get_defaultColor() {
        return _defaultColor;
    }

    bool ClickableText::get_isHighlighted() {
        return _isHighlighted;
    }

    void ClickableText::set_isHighlighted(bool value) {
        _isHighlighted = value;
        UpdateHighlight();
    }
}
