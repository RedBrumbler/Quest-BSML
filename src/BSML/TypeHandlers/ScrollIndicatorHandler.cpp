#include "BSML/TypeHandlers/ScrollIndicatorHandler.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "Helpers/utilities.hpp"

UnityEngine::UI::Image GetHandleImage(BSML::ScrollIndicator indicator) {
    return indicator.Handle.GetComponent<UnityEngine::UI::Image>();
}

void TrySetHandleColor(BSML::ScrollIndicator indicator, const StringParseHelper& htmlColor) {
    auto v = htmlColor.tryParseColor();
    if (v.has_value())
    GetHandleImage(indicator).color = v.value();
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
            { "handleColor", TrySetHandleColor },
            { "handleImage", [](auto component, auto value){ Utilities::SetImage(GetHandleImage(component), value); }}
        };
    }
}
