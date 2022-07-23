#include "BSML/Components/Settings/ToggleSetting.hpp"

#include "UnityEngine/Events/UnityAction_1.hpp"
#include "UnityEngine/UI/Toggle_ToggleEvent.hpp"

DEFINE_TYPE(BSML, ToggleSetting);

namespace BSML {
    void ToggleSetting::ctor() {
        this->base_ctor();
        currentValue = false;
    }

    void ToggleSetting::Start() {
        Setup();

        std::function<void(bool)> fun = std::bind(&ToggleSetting::OnValueChanged, this, std::placeholders::_1);
        auto delegate = il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<bool>*>(classof(UnityEngine::Events::UnityAction_1<bool>*), fun);

        toggle->onValueChanged->AddListener(delegate);
    }

    void ToggleSetting::Setup() {
        ReceiveValue();
    }

    void ToggleSetting::ReceiveValue() {
        if (!genericSetting) return;
        set_Value(genericSetting->GetValue<bool>());
    }

    void ToggleSetting::ApplyValue() {
        if (!genericSetting) return;
        genericSetting->SetValue<bool>(currentValue);
    }

    void ToggleSetting::OnValueChanged(bool value) {
        set_Value(value);

        if (genericSetting) {
            genericSetting->OnChange(currentValue);
            if (genericSetting->applyOnChange) ApplyValue();
        }
    }

    bool ToggleSetting::get_Value() {
        return currentValue;
    }
    
    void ToggleSetting::set_Value(bool value) {
        currentValue = value;
        if (toggle) toggle->set_isOn(value);
    }
    
    StringW ToggleSetting::get_text() {
        return text ? text->get_text() : "";
    }
    
    void ToggleSetting::set_text(StringW value) {
        if (text) text->set_text(value);
    }
    
    bool ToggleSetting::get_interactable() {
        return toggle && toggle->get_interactable();
    }
    
    void ToggleSetting::set_interactable(bool value) {
        if (toggle) toggle->set_interactable(value);
    }
}