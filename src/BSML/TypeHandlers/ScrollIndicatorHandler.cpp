#include "BSML/TypeHandlers/ScrollIndicatorHandler.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "Helpers/utilities.hpp"

UnityEngine::UI::Image* GetHandleImage(BSML::ScrollIndicator* indicator) {
    return indicator->get_Handle()->GetComponent<UnityEngine::UI::Image*>();
}

namespace BSML {
    static ScrollIndicatorHandler scrollIndicatorHandler{};

    ScrollIndicatorHandler::Base::PropMap ScrollIndicatorHandler::get_props() const {
        return {
            { "handleColor", {"handle-color"} },
            { "handleImage", {"handle-image"} }
        };
    }

    ScrollIndicatorHandler::Base::SetterMap ScrollIndicatorHandler::get_setters() const {
        return {
            { "handleColor", [](auto component, auto value){ auto v = value.tryParseColor(); if (v.has_value()) component->set_color(v.value()); }},
            { "handleImage", [](auto component, auto value){ Utilities::SetImage(GetHandleImage(component), value); }}
        };
    }
}
