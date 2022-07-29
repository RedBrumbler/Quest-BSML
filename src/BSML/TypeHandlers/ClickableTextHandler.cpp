#include "BSML/TypeHandlers/ClickableTextHandler.hpp"

namespace BSML {
    static ClickableTextHandler clickableTextHandler;
    ClickableTextHandler::Base::PropMap ClickableTextHandler::get_props() const {
        return {
            {"onClick", {"on-click"}},
            {"clickEvent", {"click-event", "event-click"}},
            { "highlightColor", {"highlight-color"}},
            { "defaultColor", {"default-color"}}
        };
    }

    ClickableTextHandler::Base::SetterMap ClickableTextHandler::get_setters() const {
        return {
            { "highlightColor", [](auto component, auto value){ component->set_highlightColor(value); }},
            { "defaultColor",   [](auto component, auto value){ component->set_defaultColor(value); }}
        };
    }

    void ClickableTextHandler::HandleType(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) {
        auto clickableTextOpt = il2cpp_utils::try_cast<ClickableText>(componentType.component);
        auto host = parserParams.host;

        if (clickableTextOpt.has_value()) {
            auto clickableText = clickableTextOpt.value();

            // it was a clickableText!
            auto onClickItr = componentType.data.find("onClick");
            if (onClickItr != componentType.data.end() && !onClickItr->second.empty()) {
                auto onClickMethodInfo = il2cpp_functions::class_get_method_from_name(host->klass, onClickItr->second.c_str(), 0);
                if (onClickMethodInfo) {
                    clickableText->onClick = [host, onClickMethodInfo](){ il2cpp_utils::RunMethod(host, onClickMethodInfo); };
                    
                } else {
                    ERROR("Method '{}' could not be found in class {}::{}", onClickItr->second, host->klass->namespaze, host->klass->name);
                }
            }

            auto clickEventItr = componentType.data.find("click-event");
            if (clickEventItr != componentType.data.end() && !clickEventItr->second.empty()) {
                auto clickEventMethodInfo = il2cpp_functions::class_get_method_from_name(host->klass, clickEventItr->second.c_str(), 0);
                if (clickEventMethodInfo) {
                    clickableText->onClick = [host, clickEventMethodInfo](){ il2cpp_utils::RunMethod(host, clickEventMethodInfo); };
                } else {
                    ERROR("Method '{}' could not be found in class {}::{}", clickEventItr->second, host->klass->namespaze, host->klass->name);
                }
            }
        }

        Base::HandleType(componentType, parserParams);
    }
}