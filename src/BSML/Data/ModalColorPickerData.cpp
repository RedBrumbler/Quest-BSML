#include "BSML/Data/ModalColorPickerData.hpp"
#include "internal_macros.hpp"
#include "logging.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

#include "System/Action.hpp"

namespace BSML {
    ModalColorPickerData::ModalColorPickerData(const tinyxml2::XMLElement& elem) {
        GET_BSML_STRING("value", value);
        GET_BSML_STRING("on-cancel", onCancel);
        GET_BSML_STRING("on-done", onDone);
        GET_BSML_STRING("color-change", colorChange);
    }

    void ModalColorPickerData::Apply(BSML::ModalColorPicker* colorPicker, Il2CppObject* host) const {
        if (!colorPicker || !host) {
            ERROR("nullptr passed to ModalColorPickerData::Apply");
            return;
        }

        colorPicker->host = host;

        if (!get_value().empty()) {
            auto genericSetting = colorPicker->genericSetting;
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
        
        colorPicker->onCancelInfo = il2cpp_functions::class_get_method_from_name(host->klass, get_onCancel().data(), 0);
        colorPicker->onDoneInfo = il2cpp_functions::class_get_method_from_name(host->klass, get_onDone().data(), 1);
        colorPicker->colorChangeInfo = il2cpp_functions::class_get_method_from_name(host->klass, get_colorChange().data(), 1);        
    }
}