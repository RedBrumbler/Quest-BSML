#include "BSML/TypeHandlers/ModalKeyboardHandler.hpp"

namespace BSML {
    static ModalKeyboardHandler modalKeyboardHandler{};

    ModalKeyboardHandler::Base::PropMap ModalKeyboardHandler::get_props() const {
        return {
            { "value", {"value"}},
            { "onEnter", {"on-enter"}},
            { "clearOnOpen", {"clear-on-open"}}
        };
    }

    ModalKeyboardHandler::Base::SetterMap ModalKeyboardHandler::get_setters() const {
        return {
            {"clearOnOpen", [](auto component, auto value){ component->clearOnOpen = value; }}
        };
    }

    void ModalKeyboardHandler::HandleType(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) {
        auto modalKeyboard = reinterpret_cast<BSML::ModalKeyboard*>(componentType.component);
        auto host = parserParams.get_host();
        auto& data = componentType.data;

        auto valueItr = data.find("value");
        if (valueItr != data.end() && !valueItr->second.empty()) {
            auto genericSetting = modalKeyboard->genericSetting;
            auto val = parserParams.TryGetValue(valueItr->second);
            if (val) {
                genericSetting->host = val->host;
                genericSetting->valueInfo = val->fieldInfo;
                genericSetting->getterInfo = val->getterInfo;
                genericSetting->setterInfo = val->setterInfo;
            }
        }

        auto onEnterItr = data.find("onEnter");
        if (onEnterItr != data.end() && !onEnterItr->second.empty()) {
            auto arg = StringParseHelper(onEnterItr->second);
            auto onEnterInfo = arg.asMethodInfo(host, 1);
            if (onEnterInfo)
                modalKeyboard->onEnter = [host, onEnterInfo](auto value){ il2cpp_utils::RunMethod(host, onEnterInfo, value); };
        }

        Base::HandleType(componentType, parserParams);
    }
}