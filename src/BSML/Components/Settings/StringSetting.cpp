#include "BSML/Components/Settings/StringSetting.hpp"
#include "Helpers/delegates.hpp"
#include "logging.hpp"

#include "UnityEngine/UI/Button_ButtonClickedEvent.hpp"
#include "UnityEngine/Events/UnityAction.hpp"

DEFINE_TYPE(BSML, StringSetting);

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    void StringSetting::ctor() {
        genericSetting = GenericSettingWrapper::New_ctor();
        currentValue = "";
    }

    bool StringSetting::get_interactable() {
        return editButton ? editButton.interactable : false;
    }

    void StringSetting::set_interactable(bool value) {
        if (editButton) editButton.interactable = value;
    }

    StringW StringSetting::get_text() {
        return currentValue;
    }

    void StringSetting::set_text(StringW value) {
        currentValue = value;
        if (_text)
            _text.text = formatter ? formatter(value) : value;
    }

    void StringSetting::BaseSetup() {
        modalKeyboard.onEnter = [self = *this](auto v){ self.EnterPressed(v); };

        editButton.onClick = Button::ButtonClickedEvent::New_ctor();
        auto delegate = MakeUnityAction([self = *this]{ self.EditButtonPressed()});
        editButton.onClick.AddListener(delegate);
    }

    void StringSetting::Setup() {
        modalKeyboard.clearOnOpen = false;
        ReceiveValue();
    }

    void StringSetting::EditButtonPressed() {
        modalKeyboard.modalView.Show();
        modalKeyboard.SetText(text);
    }

    void StringSetting::EnterPressed(StringW value) {
        text = value;
        if (genericSetting) {
            auto val = text;
            genericSetting->OnChange(val);
            if (genericSetting->applyOnChange) ApplyValue();
        }
    }

    void StringSetting::ApplyValue() {
        if (genericSetting)
            genericSetting.SetValue(text);
    }

    void StringSetting::ReceiveValue() {
        if (!genericSetting) return;
        text = genericSetting.GetValue<StringW>();
    }

}
