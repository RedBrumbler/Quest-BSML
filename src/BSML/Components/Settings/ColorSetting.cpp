#include "BSML/Components/Settings/ColorSetting.hpp"
#include "Helpers/delegates.hpp"
#include "logging.hpp"

#include "UnityEngine/UI/Button_ButtonClickedEvent.hpp"
#include "UnityEngine/Events/UnityAction.hpp"

DEFINE_TYPE(BSML, ColorSetting);

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    void ColorSetting::ctor() {
        genericSetting = GenericSettingWrapper::New_ctor();
        _currentColor = {1.0f, 1.0f, 1.0f, 1.0f};
    }

    UnityEngine::Color ColorSetting::get_currentColor() {
        return _currentColor;
    }

    void ColorSetting::set_currentColor(UnityEngine::Color value) {
        _currentColor = value;
        if (colorImage)
            colorImage.color = _currentColor;
    }

    bool ColorSetting::get_interactable() {
        return editButton ? editButton.interactable : false;
    }

    void ColorSetting::set_interactable(bool value) {
        if (editButton) editButton.interactable = value;
    }

    void ColorSetting::Setup() {
        if (modalColorPicker) {
            modalColorPicker->host = *this;
            auto klass = il2cpp_functions::object_get_class(*this);
            modalColorPicker.onDoneInfo = il2cpp_functions::class_get_method_from_name(klass, "DonePressed", 1);
            modalColorPicker.onCancelInfo = il2cpp_functions::class_get_method_from_name(klass, "CancelPressed", 0);
        } else {
            ERROR("No modalColorPicker found!");
        }

        auto delegate = MakeUnityAction([self = *this](){ self.EditButtonPressed(); });
        editButton.onClick = Button::ButtonClickedEvent::New_ctor();
        editButton.onClick.AddListener(delegate);
        ReceiveValue();
    }

    void ColorSetting::EditButtonPressed() {
        modalColorPicker.currentColor = currentColor;
        modalColorPicker.modalView.Show();
    }

    void ColorSetting::DonePressed(UnityEngine::Color color) {
        currentColor = color;
        if (genericSetting) {
            genericSetting.OnChange(color);
            if (genericSetting.applyOnChange) ApplyValue();
        }
    }

    void ColorSetting::CancelPressed() {
        if (genericSetting)
            genericSetting.OnChange(currentColor);
    }

    void ColorSetting::ApplyValue() {
        if (!genericSetting) return;
        genericSetting.SetValue(currentColor);
    }

    void ColorSetting::ReceiveValue() {
        if (!genericSetting) return;
        currentColor = genericSetting.GetValueOpt<UnityEngine::Color>().value_or(currentColor);
    }

}
