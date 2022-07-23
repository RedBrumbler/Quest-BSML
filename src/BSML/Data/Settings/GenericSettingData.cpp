#include "BSML/Data/Settings/GenericSettingData.hpp"
#include "internal_macros.hpp"
namespace BSML {
    GenericSettingData::GenericSettingData(const tinyxml2::XMLElement& elem) {
        GET_BSML_STRING("on-change", onChange);
        GET_BSML_STRING("value", value);
        GET_BSML_BOOL_OPT("apply-on-change", applyOnChange);
    }
    
    void GenericSettingData::Apply(BSML::GenericSettingWrapper* genericSetting, Il2CppObject* host) const {
        if (!genericSetting || !host) {
            ERROR("nullptr passed to GenericSettingData::Apply");
            return;
        }

        genericSetting->host = host;
        
        if (applyOnChange.has_value()) genericSetting->applyOnChange = applyOnChange.value();

        if (!get_onChange().empty()) {
            // the method can be void or type, so we need to check for both
            genericSetting->onChangeInfo = il2cpp_functions::class_get_method_from_name(host->klass, get_onChange().data(), 1);
            if (!genericSetting->onChangeInfo)
                genericSetting->onChangeInfo = il2cpp_functions::class_get_method_from_name(host->klass, get_onChange().data(), 0);
        }

        if (!get_value().empty()) {
            auto fieldInfo = il2cpp_functions::class_get_field_from_name(host->klass, get_value().data());
            if (fieldInfo) {
                genericSetting->valueInfo = fieldInfo;
            } else {
                std::string getterName = "get_" + get_value();
                std::string setterName = "set_" + get_value();
                
                genericSetting->getterInfo = il2cpp_functions::class_get_method_from_name(host->klass, getterName.c_str(), 0);
                genericSetting->setterInfo = il2cpp_functions::class_get_method_from_name(host->klass, setterName.c_str(), 1);
            }

        }
    }
}