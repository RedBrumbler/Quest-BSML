#include "BSML/TypeHandlers/GridLayoutHandler.hpp"
#include "UnityEngine/Vector2.hpp"

namespace BSML {
    static GridLayoutHandler gridLayoutHandler{};

    GridLayoutHandler::Base::PropMap GridLayoutHandler::get_props() const {
        return {
            {"cellSizeX", {"cell-size-x"}},
            {"cellSizeY", {"cell-size-y"}},
            {"spacingX", {"spacing-x"}},
            {"spacingY", {"spacing-y"}}
        };
    }

    GridLayoutHandler::Base::SetterMap GridLayoutHandler::get_setters() const {
        return {
            {"cellSizeX",   [](auto component, auto value){ component.cellSize = UnityEngine::Vector2(value, component.cellSize.y); }},
            {"cellSizeY",   [](auto component, auto value){ component.cellSize = UnityEngine::Vector2(component.cellSize.x, value); }},
            {"spacingX",    [](auto component, auto value){ component.spacing = UnityEngine::Vector2(value, component.spacing.y); }},
            {"spacingY",    [](auto component, auto value){ component.spacing = UnityEngine::Vector2(component.spacing.x, value); }}
        };
    }
}
