#include "BSML/TypeHandlers/HorizontalOrVerticalLayoutGroupHandler.hpp"

namespace BSML {
    static HorizontalOrVerticalLayoutGroupHandler horizontalOrVerticalLayoutGroupHandler{};

    HorizontalOrVerticalLayoutGroupHandler::Base::PropMap HorizontalOrVerticalLayoutGroupHandler::get_props() const {
        return {
            {"spacing", {"spacing"}},
            {"childForceExpandWidth", {"child-expand-width"}},
            {"childForceExpandHeight", {"child-expand-height"}},
            {"childControlWidth", {"child-control-width"}},
            {"childControlHeight", {"child-control-height"}}
        };
    }

    HorizontalOrVerticalLayoutGroupHandler::Base::SetterMap HorizontalOrVerticalLayoutGroupHandler::get_setters() const {
        return {
            {"spacing",                 [](auto component, auto value){ component.spacing = value; }},
            {"childForceExpandWidth",   [](auto component, auto value){ component.childForceExpandWidth = value; }},
            {"childForceExpandHeight",  [](auto component, auto value){ component.childForceExpandHeight = value; }},
            {"childControlWidth",       [](auto component, auto value){ component.childControlWidth = value; }},
            {"childControlHeight",      [](auto component, auto value){ component.childControlHeight = value; }}
        };
    }
}
