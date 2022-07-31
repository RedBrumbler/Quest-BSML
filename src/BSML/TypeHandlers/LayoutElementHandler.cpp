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
            {"ignoreLayout", [](auto component, auto value){ component->set_ignoreLayout(value); }},
            {"preferredWidth", [](auto component, auto value){ component->set_preferredWidth(value); }},
            {"preferredHeight", [](auto component, auto value){ component->set_preferredHeight(value); }},
            {"minHeight", [](auto component, auto value){ component->set_minHeight(value); }},
            {"minWidth", [](auto component, auto value){ component->set_minWidth(value); }}
        };
    }
}