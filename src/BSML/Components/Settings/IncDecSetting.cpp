#include "BSML/Components/Settings/IncDecSetting.hpp"

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
        auto increaseInfo = il2cpp_functions::class_get_method_from_name(this->klass, "IncButtonPressed", 0);
        if (increaseInfo) {
            auto onClick = incButton->get_onClick();
            // all our args are by value, so they remain valid even after this method returns
            std::function<void()> fun = [host=this, increaseInfo]() -> void { il2cpp_utils::RunMethod(host, increaseInfo); };
            auto delegate = il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction*>(classof(UnityEngine::Events::UnityAction*), fun);
            onClick->AddListener(delegate);
        }

        auto decreaseInfo = il2cpp_functions::class_get_method_from_name(this->klass, "DecButtonPressed", 0);
        if (decreaseInfo) {
            auto onClick = decButton->get_onClick();
            std::function<void()> fun = [host=this, decreaseInfo]() -> void { il2cpp_utils::RunMethod(host, decreaseInfo); };
            auto delegate = il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction*>(classof(UnityEngine::Events::UnityAction*), fun);
            onClick->AddListener(delegate);
        }
    }

    bool IncDecSetting::get_interactable() {
        return interactable;
    }

    void IncDecSetting::set_interactable(bool value) {
        if (interactable == value) return;
        interactable = value;
        set_enableDec(enableDec);
        set_enableInc(enableInc);
    }

    void IncDecSetting::set_enableDec(bool value) {
        enableDec = value;
        decButton->set_interactable(enableDec && interactable);
    }

    void IncDecSetting::set_enableInc(bool value) {
        enableInc = value;
        incButton->set_interactable(enableInc && interactable);
    }

    void IncDecSetting::set_text(StringW value) {
        text->set_text(value);
    }
}