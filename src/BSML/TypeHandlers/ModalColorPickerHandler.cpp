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
        auto host = parserParams.get_host();
        auto& data = componentType.data;

        colorPicker->host = host;
        auto valueItr = data.find("value");
        if (valueItr != data.end()) {
            auto val = parserParams.TryGetValue(valueItr->second);
            auto genericSetting = colorPicker->genericSetting;
            if (val) {
                genericSetting->host = val->host;
                genericSetting->valueInfo = val->fieldInfo;
                genericSetting->getterInfo = val->getterInfo;
                genericSetting->setterInfo = val->setterInfo;
            }
        }

        auto onCancelItr = data.find("onCancel");
        if (onCancelItr != data.end() && !onCancelItr->second.empty()) {
            colorPicker->onCancelInfo = StringParseHelper(onCancelItr->second).asMethodInfo(host, 0);
        }
        auto onDoneItr = data.find("onDone");
        if (onDoneItr != data.end() && !onDoneItr->second.empty()) {
            colorPicker->onDoneInfo = StringParseHelper(onDoneItr->second).asMethodInfo(host, 1);
        }
        auto onChangeItr = data.find("onChange");
        if (onChangeItr != data.end() && !onChangeItr->second.empty()) {
            colorPicker->colorChangeInfo = StringParseHelper(onChangeItr->second).asMethodInfo(host, 1);
        }

        Base::HandleType(componentType, parserParams);
    }
}