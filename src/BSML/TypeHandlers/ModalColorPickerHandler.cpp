#include "BSML/TypeHandlers/ModalColorPickerHandler.hpp"

namespace BSML {
    ModalColorPickerHandler modalColorPickerHandler{};

    ModalColorPickerHandler::Base::PropMap ModalColorPickerHandler::get_props() const {
        return {
            {"value", {"value"}},
            {"onCancel", {"on-cancel"}},
            {"onDone", {"on-done"}},
            {"onChange", {"color-change"}}
        };
    }

    ModalColorPickerHandler::Base::SetterMap ModalColorPickerHandler::get_setters() const {
        return {};
    }

    void ModalColorPickerHandler::HandleType(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) {
        auto colorPicker = reinterpret_cast<ModalColorPicker*>(componentType.component);
        auto host = parserParams.host;
        auto& data = componentType.data;

        colorPicker->host = host;
        auto valueItr = data.find("value");
        if (valueItr != data.end()) {
            auto genericSetting = colorPicker->genericSetting;
            auto fieldInfo = il2cpp_functions::class_get_field_from_name(host->klass, valueItr->second.c_str());

            if (fieldInfo) {
                genericSetting->valueInfo = fieldInfo;
            } else {
                std::string getterName = "get_" + valueItr->second;
                std::string setterName = "set_" + valueItr->second;

                genericSetting->getterInfo = il2cpp_functions::class_get_method_from_name(host->klass, getterName.c_str(), 0);
                genericSetting->setterInfo = il2cpp_functions::class_get_method_from_name(host->klass, setterName.c_str(), 1);
            }
        }

        auto onCancelItr = data.find("onCancel");
        if (onCancelItr != data.end()) {
            colorPicker->onCancelInfo = il2cpp_functions::class_get_method_from_name(host->klass, onCancelItr->second.c_str(), 0);
        }
        auto onDoneItr = data.find("onDone");
        if (onDoneItr != data.end()) {
            colorPicker->onDoneInfo = il2cpp_functions::class_get_method_from_name(host->klass, onDoneItr->second.c_str(), 1);
        }
        auto onChangeItr = data.find("onChange");
        if (onChangeItr != data.end()) {
            colorPicker->colorChangeInfo = il2cpp_functions::class_get_method_from_name(host->klass, onChangeItr->second.c_str(), 1);        
        }

        Base::HandleType(componentType, parserParams);
    }
}