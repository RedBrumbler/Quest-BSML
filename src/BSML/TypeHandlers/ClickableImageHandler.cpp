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
            { "highlightColor", [](auto component, auto value){ component.highlightColor = value; }},
            { "defaultColor",   [](auto component, auto value){ component.defaultColor = value; }}
        };
    }

    void ClickableImageHandler::HandleTypeAfterParse(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) {
        ClickableImage clickableImage { componentType.component.convert()};

        auto onClickItr = componentType.data.find("onClick");
        if (onClickItr != componentType.data.end() && !onClickItr->second.empty()) {
            auto action = parserParams.TryGetAction(onClickItr->second);
            if (action) clickableImage.onClick += action->GetFunction();
            else ERROR("Action '{}' could not be found", onClickItr->second);
        }

        auto clickEventItr = componentType.data.find("click-event");
        if (clickEventItr != componentType.data.end() && !clickEventItr->second.empty()) {
            auto parserEvent = parserParams.GetEvent(clickEventItr->second);
            clickableImage.onClick += [parserEvent](){
                if (!parserEvent.expired()) {
                    parserEvent.lock()->Invoke();
                } else {
                    ERROR("Event pointer expired, are you saving your parser params?");
                }
            };
        }

        Base::HandleTypeAfterParse(componentType, parserParams);
    }
}
