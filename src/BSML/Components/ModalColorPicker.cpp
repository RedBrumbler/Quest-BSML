#include "BSML/Components/ModalColorPicker.hpp"

DEFINE_TYPE(BSML, ModalColorPicker);

namespace BSML {
    void ModalColorPicker::ctor() {
        genericSetting = GenericSettingWrapper::New_ctor();
        _currentColor = {1.0f, 1.0f, 1.0f, 1.0f};
    }

    UnityEngine::Color ModalColorPicker::get_currentColor() {
        return _currentColor;
    }

    void ModalColorPicker::set_currentColor(UnityEngine::Color value) {
        _currentColor = value;
        if (rgbPanel)
            rgbPanel.color = value;
        if (hsvPanel && hsvPanel.color != value) // this check is because if the color change doesn't change hue and you apply anyways, it locks up
            hsvPanel.color = value;
        if (colorImage)
            colorImage.color = value;
    }

    void ModalColorPicker::OnEnable() {
        if (genericSetting)
            currentColor = genericSetting.GetValueOpt<UnityEngine::Color>().value_or(currentColor);
    }

    void ModalColorPicker::CancelPressed() {
        if (cancel) cancel();
        if (host && onCancelInfo) il2cpp_utils::RunMethod(host, onCancelInfo);
        modalView.Hide();
    }

    void ModalColorPicker::DonePressed() {
        if (done) done(currentColor);
        if (host && onDoneInfo) il2cpp_utils::RunMethod(host, onDoneInfo, currentColor);
        if (genericSetting)
            genericSetting.SetValue(currentColor);
        modalView.Hide();
    }

    void ModalColorPicker::OnChange(UnityEngine::Color value, GlobalNamespace::ColorChangeUIEventType type) {
        if (onChange) onChange(value);
        if (host && colorChangeInfo) il2cpp_utils::RunMethod(host, colorChangeInfo, currentColor);
        if (genericSetting)
            genericSetting.OnChange(value);
        currentColor = value;
    }
}
