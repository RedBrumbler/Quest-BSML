#include "BSML/TypeHandlers/BackgroundableHandler.hpp"
#include "Helpers/utilities.hpp"

namespace BSML {
    static BackgroundableHandler backgroundableHandler{};

    BackgroundableHandler::Base::PropMap BackgroundableHandler::get_props() const {
        return {
            {"background", {"bg", "background"}},
            {"backgroundColor", {"bg-color", "background-color"}},
            {"backgroundAlpha", {"bg-alpha"}}
        };
    }

    BackgroundableHandler::Base::SetterMap BackgroundableHandler::get_setters() const {
        return {
            {"background", [](auto component, auto value){ component->ApplyBackground(value); }},
            {"backgroundColor", [](auto component, auto value){ component->ApplyColor(value); }},
            {"backgroundAlpha", [](auto component, auto value){ component->ApplyAlpha(value); }}
        };
    }
}