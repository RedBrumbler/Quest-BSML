#include "BSML/Data/Settings/ListSettingData.hpp"
#include "logging.hpp"
#include "BSMLMacros.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

namespace BSML {
    ListSettingData::ListSettingData(const tinyxml2::XMLElement& elem) {
        GET_BSML_STRING("list-options", listOptions);
        GET_BSML_STRING("options", listOptions);

        GET_BSML_STRING("list-choice", listChoice);
        GET_BSML_STRING("choice", listChoice);
    }

    void ListSettingData::Apply(BSML::ListSetting* listSetting, Il2CppObject* host) const {
        if (!listSetting || !host) {
            ERROR("nullptr passed to ListSettingData::Apply");
            return;
        }

        auto optionsInfo = il2cpp_functions::class_get_field_from_name(host->klass, listOptions.c_str());
        if (optionsInfo) {
            listSetting->values = il2cpp_functions::field_get_value_object(optionsInfo, host);
        }

        auto choiceInfo = il2cpp_functions::class_get_field_from_name(host->klass, listChoice.c_str());
        if (choiceInfo) {
            listSetting->set_Value(il2cpp_functions::field_get_value_object(choiceInfo, host));
        }
    }
}