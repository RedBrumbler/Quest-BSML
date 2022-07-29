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
            {"cellSizeX",   [](auto component, auto value){ component->set_cellSize(UnityEngine::Vector2(value, component->get_cellSize().y)); }},
            {"cellSizeY",   [](auto component, auto value){ component->set_cellSize(UnityEngine::Vector2(component->get_cellSize().x, value)); }},
            {"spacingX",    [](auto component, auto value){ component->set_spacing(UnityEngine::Vector2(value, component->get_spacing().y)); }},
            {"spacingY",    [](auto component, auto value){ component->set_spacing(UnityEngine::Vector2(component->get_spacing().x, value)); }}
        };
    }
}