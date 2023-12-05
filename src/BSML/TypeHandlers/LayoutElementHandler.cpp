#include "BSML/TypeHandlers/LayoutElementHandler.hpp"

namespace BSML {
    static LayoutElementHandler layoutElementHandler{};

    LayoutElementHandler::Base::PropMap LayoutElementHandler::get_props() const {
        return {
            {"ignoreLayout", {"ignore-layout"}},
            {"preferredWidth", {"preferred-width", "pref-width"}},
            {"preferredHeight", {"preferred-height", "pref-height"}},
            {"minHeight", {"min-height"}},
            {"minWidth", {"min-width"}}
        };
    }

    LayoutElementHandler::Base::SetterMap LayoutElementHandler::get_setters() const {
        return {
            {"ignoreLayout", [](auto component, auto value){ component.ignoreLayout = value; }},
            {"preferredWidth", [](auto component, auto value){ component.preferredWidth = value; }},
            {"preferredHeight", [](auto component, auto value){ component.preferredHeight = value; }},
            {"minHeight", [](auto component, auto value){ component.minHeight = value; }},
            {"minWidth", [](auto component, auto value){ component.minWidth = value; }}
        };
    }
}
