#include "BSML/TypeHandlers/ClickableImageHandler.hpp"

namespace BSML {
    static ClickableImageHandler clickableImageHandler;
    ClickableImageHandler::Base::PropMap ClickableImageHandler::get_props() const {
        return {
            {"onClick", {"on-click"}},
            {"clickEvent", {"click-event", "event-click"}},
            { "highlightColor", {"highlight-color"}},
            { "defaultColor", {"default-color"}}
        };
    }

    ClickableImageHandler::Base::SetterMap ClickableImageHandler::get_setters() const {
        return {
            { "highlightColor", [](auto component, auto value){ component->set_highlightColor(value); }},
            { "defaultColor",   [](auto component, auto value){ component->set_defaultColor(value); }}
        };
    }

    void ClickableImageHandler::HandleType(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) {
        auto clickableImageOpt = il2cpp_utils::try_cast<ClickableImage>(componentType.component);
        auto host = parserParams.get_host();

        if (clickableImageOpt.has_value()) {
            auto clickableImage = clickableImageOpt.value();

            // it was a clickableImage!
            auto onClickItr = componentType.data.find("onClick");
            if (onClickItr != componentType.data.end() && !onClickItr->second.empty()) {
                auto onClickMethodInfo = il2cpp_functions::class_get_method_from_name(host->klass, onClickItr->second.c_str(), 0);
                if (onClickMethodInfo) {
                    clickableImage->onClick = [host, onClickMethodInfo](){ il2cpp_utils::RunMethod(host, onClickMethodInfo); };
                    
                } else {
                    ERROR("Method '{}' could not be found in class {}::{}", onClickItr->second, host->klass->namespaze, host->klass->name);
                }
            }

            auto clickEventItr = componentType.data.find("click-event");
            if (clickEventItr != componentType.data.end() && !clickEventItr->second.empty()) {
                auto clickEventMethodInfo = il2cpp_functions::class_get_method_from_name(host->klass, clickEventItr->second.c_str(), 0);
                if (clickEventMethodInfo) {
                    clickableImage->onClick = [host, clickEventMethodInfo](){ il2cpp_utils::RunMethod(host, clickEventMethodInfo); };
                } else {
                    ERROR("Method '{}' could not be found in class {}::{}", clickEventItr->second, host->klass->namespaze, host->klass->name);
                }
            }
        }

        Base::HandleType(componentType, parserParams);
    }
}