#include "BSML/Components/Settings/IncDecSetting.hpp"
#include "Helpers/delegates.hpp"

#include "UnityEngine/Events/UnityAction.hpp"
#include "UnityEngine/UI/Button_ButtonClickedEvent.hpp"

DEFINE_TYPE(BSML, IncDecSetting);

namespace BSML {
    void IncDecSetting::construct() {
        genericSetting = GenericSettingWrapper::New_ctor();
        interactable = true;
        enableDec = true;
        enableInc = true;
    }

    void IncDecSetting::BaseSetup() {
        // we use reflection since we can't do proper virtual methods
        auto klass = il2cpp_functions::object_get_class(*this);
        auto increaseInfo = il2cpp_functions::class_get_method_from_name(klass, "IncButtonPressed", 0);
        if (increaseInfo) {
            auto onClick = incButton.onClick;
            auto delegate = MakeUnityAction(*this, increaseInfo);
            onClick.AddListener(delegate);
        }

        auto decreaseInfo = il2cpp_functions::class_get_method_from_name(klass, "DecButtonPressed", 0);
        if (decreaseInfo) {
            auto onClick = decButton.onClick;
            auto delegate = MakeUnityAction(*this, decreaseInfo);
            onClick.AddListener(delegate);
        }
    }

    bool IncDecSetting::get_interactable() {
        return _interactable;
    }

    void IncDecSetting::set_interactable(bool value) {
        if (_interactable == value) return;
        _interactable = value;
        enableDec = _enableDec;
        enableInc = _enableInc;
    }

    void IncDecSetting::set_enableDec(bool value) {
        enableDec = value;
        decButton.interactable = _enableDec && interactable;
    }

    void IncDecSetting::set_enableInc(bool value) {
        enableInc = value;
        incButton.interactable = _enableInc && interactable;
    }

    void IncDecSetting::set_text(StringW value) {
        text.text = value;
    }
}
