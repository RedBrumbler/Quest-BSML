#include "BSML/Data/Settings/ToggleSettingData.hpp"
#include "logging.hpp"
#include "BSMLMacros.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

#include "UnityEngine/Transform.hpp"
#include "UnityEngine/GameObject.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

#include "UnityEngine/UI/Toggle_ToggleEvent.hpp"
#include "UnityEngine/Events/UnityAction_1.hpp"

#define MakeDelegate(DelegateType, varName) (il2cpp_utils::MakeDelegate<DelegateType>(classof(DelegateType), varName))

UnityEngine::Events::UnityAction_1<bool>* MakeToggleCallback(const MethodInfo* setterInfo, FieldInfo* fieldInfo, const MethodInfo* onChangeInfo, Il2CppObject* host);

namespace BSML {
    ToggleSettingData::ToggleSettingData(const tinyxml2::XMLElement& elem) {
        GET_BSML_STRING("on-text", onText);
        GET_BSML_STRING("on-label", onText);
        GET_BSML_STRING("off-text", offText);
        GET_BSML_STRING("off-label", offText);
        
        GET_BSML_STRING("field-name", fieldName);
        GET_BSML_STRING("field", fieldName);
        
        GET_BSML_STRING("on-change", onChange);
        GET_BSML_STRING("on-toggle", onChange);
        
        GET_BSML_STRING("property-name", propertyName);
        GET_BSML_STRING("property", propertyName);

        GET_BSML_BOOL("start-value", startValue);
    }

    void ToggleSettingData::Apply(UnityEngine::UI::Toggle* toggle, Il2CppObject* host) const {
        if (!toggle || !host) {
            ERROR("nullptr passed to ToggleSettingData::Apply");
            return;
        }

        bool startValue = get_startValue();

        toggle->onValueChanged = UnityEngine::UI::Toggle::ToggleEvent::New_ctor();
        
        std::string setterName = "set_" + propertyName;
        std::string getterName = "get_" + propertyName;
        auto setterInfo = il2cpp_functions::class_get_method_from_name(host->klass, setterName.c_str(), 1);
        auto getterInfo = il2cpp_functions::class_get_method_from_name(host->klass, getterName.c_str(), 0);

        if (getterInfo) {
            auto valOpt = il2cpp_utils::RunMethod<bool>(host, getterInfo);
            if (valOpt) startValue = valOpt.value();
        }

        auto fieldInfo = il2cpp_functions::class_get_field_from_name(host->klass, fieldName.c_str());
        if (fieldInfo) {
            startValue = il2cpp_utils::GetFieldValue<bool>(host, fieldInfo).value_or(this->startValue);
        }

        auto onChangeInfo = il2cpp_functions::class_get_method_from_name(host->klass, onChange.c_str(), 0);
        toggle->onValueChanged->AddListener(MakeToggleCallback(setterInfo, fieldInfo, onChangeInfo, host));
        toggle->set_isOn(startValue);

        auto transform = toggle->get_transform();
        if (get_onText().has_value()) {
            auto onTextObject = transform->Find("BackgroundImage/OnText")->get_gameObject()->GetComponent<TMPro::TextMeshProUGUI*>();
            onTextObject->set_text(get_onText().value());
        }

        if (get_offText().has_value()) {
            auto offTextObject = transform->Find("BackgroundImage/OffText")->get_gameObject()->GetComponent<TMPro::TextMeshProUGUI*>();
            offTextObject->set_text(get_offText().value());
        }
    }
}

UnityEngine::Events::UnityAction_1<bool>* MakeToggleCallback(const MethodInfo* setterInfo, FieldInfo* fieldInfo, const MethodInfo* onChangeInfo, Il2CppObject* host) {
    // would it be faster to make seperate callbacks for each possibility? yes.
    // do I care? no.
    std::function<void(bool)> fun = [setterInfo, fieldInfo, onChangeInfo, host] (bool value) { 
        if (setterInfo) il2cpp_utils::RunMethod(host, setterInfo, value);
        if (fieldInfo) il2cpp_utils::SetFieldValue(host, fieldInfo, value);
        if (onChangeInfo) il2cpp_utils::RunMethod(host, onChangeInfo);
    };

    return il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<bool>*>(classof(UnityEngine::Events::UnityAction_1<bool>*), fun);
}