#include "BSML/Data/ModalKeyboardData.hpp"
#include "internal_macros.hpp"
#include "logging.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

#include "System/Action.hpp"

namespace BSML {
    ModalKeyboardData::ModalKeyboardData(const tinyxml2::XMLElement& elem) {
        GET_BSML_STRING("value", value);
        GET_BSML_STRING("on-enter", onEnter);

        GET_BSML_BOOL_OPT("clear-on-open", clearOnOpen);
    }

    void ModalKeyboardData::Apply(BSML::ModalKeyboard* modalKeyboard, Il2CppObject* host) const {
        if (!modalKeyboard || !host) {
            ERROR("nullptr passed to ModalKeyboardData::Apply");
            return;
        }

        if (get_clearOnOpen().has_value()) modalKeyboard->clearOnOpen = get_clearOnOpen().value();
        auto onEnterInfo = il2cpp_functions::class_get_method_from_name(host->klass, onEnter.c_str(), 1);
        if (onEnterInfo) {
            modalKeyboard->onEnter = [host, onEnterInfo](auto value){ il2cpp_utils::RunMethod(host, onEnterInfo, value); };
        }

        // genericsetting is just really useful for stuff like this
        if (!get_value().empty()) {
            auto genericSetting = modalKeyboard->genericSetting;
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