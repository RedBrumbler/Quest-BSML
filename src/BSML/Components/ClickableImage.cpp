#include "BSML/Components/ClickableImage.hpp"
#include "logging.hpp"

#include "VRUIControls/VRPointer.hpp"

DEFINE_TYPE(BSML, ClickableImage);

namespace BSML {
    void ClickableImage::ctor() {
        INVOKE_CTOR();
        isHighlighted = false;
        highlightColor = UnityEngine::Color(0.60f, 0.80f, 1.0f, 1.0f);
        defaultColor = UnityEngine::Color(1.0f, 1.0f, 1.0f, 1.0f);

        onEnter = nullptr;
        onExit = nullptr;

        buttonClickedSignal = nullptr;
        hapticFeedbackController = nullptr;
        hapticFeedbackPresetSO = nullptr;

        INVOKE_BASE_CTOR(classof(HMUI::ImageView));
    }

    void ClickableImage::UpdateHighlight() {
        color = isHighlighted ? highlightColor : defaultColor;
    }

    void ClickableImage::OnPointerClick(UnityEngine::EventSystems::PointerEventData eventData) {
        INFO("Click");
        if (buttonClickedSignal) buttonClickedSignal.Raise();
        isHighlighted = false;
        if (onClick.size() > 0) onClick.invoke();
    }

    void ClickableImage::OnPointerEnter(UnityEngine::EventSystems::PointerEventData eventData) {
        INFO("Enter");
        isHighlighted = true;
        if (onEnter) onEnter();
        Vibrate(!VRUIControls::VRPointer::_get__lastControllerUsedWasRight());
    }

    void ClickableImage::OnPointerExit(UnityEngine::EventSystems::PointerEventData eventData) {
        INFO("Exit");
        isHighlighted = false;
        if (onExit) onExit();
    }

    void ClickableImage::Vibrate(bool left)
    {
        UnityEngine::XR::XRNode node = left ? UnityEngine::XR::XRNode::LeftHand : UnityEngine::XR::XRNode::RightHand;
        if (hapticFeedbackController && hapticFeedbackPresetSO) hapticFeedbackController.PlayHapticFeedback(node, hapticFeedbackPresetSO);
    }

    void ClickableImage::set_highlightColor(UnityEngine::Color color) {
        _highlightColor = color;
        UpdateHighlight();
    }

    UnityEngine::Color ClickableImage::get_highlightColor() {
        return _highlightColor;
    }

    void ClickableImage::set_defaultColor(UnityEngine::Color color) {
        _defaultColor = color;
        UpdateHighlight();
    }

    UnityEngine::Color ClickableImage::get_defaultColor() {
        return _defaultColor;
    }

    bool ClickableImage::get_isHighlighted() {
        return _isHighlighted;
    }

    void ClickableImage::set_isHighlighted(bool value) {
        _isHighlighted = value;
        UpdateHighlight();
    }
}
