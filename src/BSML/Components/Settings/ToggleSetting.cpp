#include "BSML/Components/Settings/ToggleSetting.hpp"
#include "Helpers/delegates.hpp"

#include "UnityEngine/Events/UnityAction_1.hpp"
#include "UnityEngine/UI/Toggle_ToggleEvent.hpp"

DEFINE_TYPE(BSML, ToggleSetting);

namespace BSML {
    void ToggleSetting::ctor() {
        genericSetting = GenericSettingWrapper::New_ctor();
        currentValue = false;
    }

    void ToggleSetting::Setup() {
        auto onValueChangedInfo = il2cpp_functions::class_get_method_from_name(il2cpp_functions::object_get_class(convert()), "OnValueChanged", 1);
        auto delegate = MakeUnityAction<bool>(*this, onValueChangedInfo);
        toggle.onValueChanged.AddListener(delegate);

        ReceiveValue();
    }

    void ToggleSetting::ReceiveValue() {
        if (!genericSetting) return;
        set_Value(genericSetting.GetValue<bool>());
    }

    void ToggleSetting::ApplyValue() {
        if (!genericSetting) return;
        genericSetting.SetValue<bool>(currentValue);
    }

    void ToggleSetting::OnValueChanged(bool value) {
        set_Value(value);

        if (genericSetting) {
            genericSetting.OnChange(currentValue);
            if (genericSetting.applyOnChange) ApplyValue();
        }
    }

    bool ToggleSetting::get_Value() {
        return currentValue;
    }

    void ToggleSetting::set_Value(bool value) {
        currentValue = value;
        if (toggle) toggle.isOn = value;
    }

    StringW ToggleSetting::get_text() {
        return _text ? _text.text : "";
    }

    void ToggleSetting::set_text(StringW value) {
        if (_text) _text.text = value;
    }

    bool ToggleSetting::get_interactable() {
        return toggle && toggle.interactable;
    }

    void ToggleSetting::set_interactable(bool value) {
        if (toggle) toggle.interactable = value;
    }
}
