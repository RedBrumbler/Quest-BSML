#include "BSML/Data/Settings/ListSettingData.hpp"
#include "logging.hpp"
#include "internal_macros.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

namespace BSML {
    ListSettingData::ListSettingData(const tinyxml2::XMLElement& elem) {
        GET_BSML_STRING("list-options", listOptions);
        GET_BSML_STRING("options", listOptions);
    }

    void ListSettingData::Apply(BSML::ListSetting* listSetting, Il2CppObject* host) const {
        if (!listSetting || !host) {
            ERROR("nullptr passed to ListSettingData::Apply");
            return;
        }

        if (!get_listOptions().empty()) {
            auto optionsInfo = il2cpp_functions::class_get_field_from_name(host->klass, get_listOptions().c_str());
            if (optionsInfo) {
                listSetting->values = il2cpp_functions::field_get_value_object(optionsInfo, host);
            } else {
                auto getterInfo = il2cpp_functions::class_get_method_from_name(host->klass, ("get_" + get_listOptions()).c_str(), 0);
                if (getterInfo) {
                    auto list = il2cpp_utils::RunMethod<List<Il2CppObject*>*>(host, getterInfo);
                    if (list.has_value())
                        listSetting->values = list.value();
                }
            }
        }
    }

    void ListSettingData::Apply(BSML::ListSliderSetting* listSetting, Il2CppObject* host) const {
        if (!listSetting || !host) {
            ERROR("nullptr passed to ListSettingData::Apply");
            return;
        }

        if (!get_listOptions().empty()) {
            auto optionsInfo = il2cpp_functions::class_get_field_from_name(host->klass, get_listOptions().c_str());
            if (optionsInfo) {
                listSetting->values = il2cpp_functions::field_get_value_object(optionsInfo, host);
            } else {
                auto getterInfo = il2cpp_functions::class_get_method_from_name(host->klass, ("get_" + get_listOptions()).c_str(), 0);
                if (getterInfo) {
                    auto list = il2cpp_utils::RunMethod<List<Il2CppObject*>*>(host, getterInfo);
                    if (list.has_value())
                        listSetting->values = list.value();
                }
            }
        }
    }

    void ListSettingData::Apply(BSML::DropdownListSetting* listSetting, Il2CppObject* host) const {
        if (!listSetting || !host) {
            ERROR("nullptr passed to ListSettingData::Apply");
            return;
        }

        if (!get_listOptions().empty()) {
            auto optionsInfo = il2cpp_functions::class_get_field_from_name(host->klass, get_listOptions().c_str());
            if (optionsInfo) {
                listSetting->values = il2cpp_functions::field_get_value_object(optionsInfo, host);
            } else {
                auto getterInfo = il2cpp_functions::class_get_method_from_name(host->klass, ("get_" + get_listOptions()).c_str(), 0);
                if (getterInfo) {
                    INFO("Using getter");
                    auto list = il2cpp_utils::RunMethod<List<Il2CppObject*>*>(host, getterInfo);
                    if (list.has_value())
                        listSetting->values = list.value();
                }
            }
        }
    }

}