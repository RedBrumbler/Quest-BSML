#include "BSML/Components/ModalColorPicker.hpp"

DEFINE_TYPE(BSML, ModalColorPicker);

namespace BSML {
    void ModalColorPicker::ctor() {
        genericSetting = GenericSettingWrapper::New_ctor();
    }

    UnityEngine::Color ModalColorPicker::get_currentColor() {
        return currentColor;
    }

    void ModalColorPicker::set_currentColor(UnityEngine::Color value) {
        currentColor = value;
        if (rgbPanel)
            rgbPanel->set_color(currentColor);
        if (hsvPanel && hsvPanel->get_color() != currentColor) // this check is because if the color change doesn't change hue and you apply anyways, it locks up
            hsvPanel->set_color(currentColor);
        if (colorImage)
            colorImage->set_color(currentColor);
    }

    void ModalColorPicker::OnEnable() {
        if (genericSetting)
            set_currentColor(genericSetting->GetValue<UnityEngine::Color>());
    }

    void ModalColorPicker::CancelPressed() {
        if (cancel) cancel();
        if (onCancelInfo) il2cpp_utils::RunMethod(host, onCancelInfo);
        modalView->Hide();
    }

    void ModalColorPicker::DonePressed() {
        if (done) done(currentColor);
        if (onDoneInfo) il2cpp_utils::RunMethod(host, onDoneInfo, currentColor);
        if (genericSetting)
            genericSetting->SetValue(currentColor);
        modalView->Hide();
    }

    void ModalColorPicker::OnChange(UnityEngine::Color value, GlobalNamespace::ColorChangeUIEventType type) {
        if (onChange) onChange(value);
        if (colorChangeInfo) il2cpp_utils::RunMethod(host, colorChangeInfo, currentColor);
        if (genericSetting)
            genericSetting->OnChange(value);
        set_currentColor(value);
    }
}