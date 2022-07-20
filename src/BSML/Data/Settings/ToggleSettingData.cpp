#include "BSML/Data/Settings/ToggleSettingData.hpp"
#include "logging.hpp"
#include "BSMLMacros.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

#include "UnityEngine/UI/Toggle_ToggleEvent.hpp"
#include "UnityEngine/Events/UnityAction_1.hpp"

#define MakeDelegate(DelegateType, varName) (il2cpp_utils::MakeDelegate<DelegateType>(classof(DelegateType), varName))

namespace BSML {
    ToggleSettingData::ToggleSettingData(const tinyxml2::XMLElement& elem) {
        GET_BSML_STRING("field-name", fieldName);
        GET_BSML_STRING("field", fieldName);
        
        GET_BSML_STRING("on-change", onChange);
        GET_BSML_STRING("on-toggle", onChange);
        
        GET_BSML_STRING("property-name", propertyName);
        GET_BSML_STRING("property", propertyName);
    }

    void ToggleSettingData::Apply(UnityEngine::UI::Toggle* toggle, Il2CppObject* host) const {
        if (!toggle || !host) {
            ERROR("nullptr passed to ToggleSettingData::Apply");
            return;
        }
        bool startValue;

        toggle->onValueChanged = UnityEngine::UI::Toggle::ToggleEvent::New_ctor();

        if (!propertyName.empty()) {
            std::string setterName = "set_" + propertyName;
            std::string getterName = "get_" + propertyName;
            auto setterInfo = il2cpp_functions::class_get_method_from_name(host->klass, setterName.c_str(), 1);
            auto getterInfo = il2cpp_functions::class_get_method_from_name(host->klass, getterName.c_str(), 0);

            startValue = il2cpp_utils::RunMethod<bool>(host, getterInfo).value_or(false);

            std::function<void(bool)> fun = [setterInfo, host] (bool value) { il2cpp_utils::RunMethod(host, setterInfo, value); };
            auto delegate = MakeDelegate(UnityEngine::Events::UnityAction_1<bool>*, fun);
            toggle->onValueChanged->AddListener(delegate);
        }
        
        if (!fieldName.empty()) {
            auto fieldInfo = il2cpp_functions::class_get_field_from_name(host->klass, fieldName.c_str());
            startValue = il2cpp_utils::GetFieldValue<bool>(host, fieldInfo).value_or(false);

            std::function<void(bool)> fun = [fieldInfo, host] (bool value) { il2cpp_utils::SetFieldValue(host, fieldInfo, value); };
            auto delegate = MakeDelegate(UnityEngine::Events::UnityAction_1<bool>*, fun);
            toggle->onValueChanged->AddListener(delegate);
        }
        
        if (!onChange.empty()) {
            auto onChangeInfo = il2cpp_functions::class_get_method_from_name(host->klass, onChange.c_str(), 0);
            
            std::function<void(bool)> fun = [onChangeInfo, host] (bool value) { il2cpp_utils::RunMethod(host, onChangeInfo); };
            auto delegate = MakeDelegate(UnityEngine::Events::UnityAction_1<bool>*, fun);
            toggle->onValueChanged->AddListener(delegate);
        }
    }
}