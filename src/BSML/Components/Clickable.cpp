#include "BSML/Components/Clickable.hpp"
#include "VRUIControls/VRPointer.hpp"

DEFINE_TYPE(BSML, Clickable);
using HapticPresetSO = Libraries::HM::HMLib::VR::HapticPresetSO;

namespace BSML {
    GlobalNamespace::Signal* get_textClickedSignal();
    HapticPresetSO* get_textHapticPreset();
    GlobalNamespace::HapticFeedbackController* get_textHapticFeedbackController();

    void Clickable::ctor() {
        INVOKE_CTOR();
        INVOKE_BASE_CTOR(classof(HMUI::Touchable*));
    }

    void Clickable::Awake() {
        buttonClickedSignal = get_textClickedSignal();
        hapticFeedbackPresetSO = get_textHapticPreset();
        hapticFeedbackController = get_textHapticFeedbackController();
    }

    void Clickable::Vibrate(bool left)
    {
        UnityEngine::XR::XRNode node = left ? UnityEngine::XR::XRNode::LeftHand : UnityEngine::XR::XRNode::RightHand;
        if (hapticFeedbackController && hapticFeedbackPresetSO) hapticFeedbackController->PlayHapticFeedback(node, hapticFeedbackPresetSO);
    }

    void Clickable::OnPointerClick(UnityEngine::EventSystems::PointerEventData* eventData) {
        auto onClick = this->onClick;
        if (buttonClickedSignal) buttonClickedSignal->Raise();
        onClick.invoke();
    }

    void Clickable::OnPointerEnter(UnityEngine::EventSystems::PointerEventData* eventData) {
        auto onEnter = this->onEnter;
        onEnter.invoke();
        Vibrate(!VRUIControls::VRPointer::_get__lastControllerUsedWasRight());
    }

    void Clickable::OnPointerExit(UnityEngine::EventSystems::PointerEventData* eventData) {
        auto onExit = this->onExit;
        onExit.invoke();
    }
}
