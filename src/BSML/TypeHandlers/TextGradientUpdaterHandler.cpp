#include "BSML/TypeHandlers/TextGradientUpdaterHandler.hpp"

namespace BSML {
    static TextGradientUpdaterHandler textGradientUpdaterHandler{};

    TextGradientUpdaterHandler::Base::PropMap TextGradientUpdaterHandler::get_props() const {
        return {
            { "gradientScrollSpeed", {"gradient-speed", "gradient-scroll-speed"}},
            { "gradientScrollRepeat", {"gradient-section", "gradient-scroll-section", "gradient-repeat"}},
            { "gradientColors", {"gradient", "gradient-colors"}}
        };
    }

    TextGradientUpdaterHandler::Base::SetterMap TextGradientUpdaterHandler::get_setters() const {
        return {
            { "gradientScrollSpeed",    [](auto component, auto value){ component->scrollSpeed = value; }},
            { "gradientScrollRepeat",   [](auto component, auto value){ component->scrollRepeat = value; }},
            { "gradientColors",         [](auto component, auto value){ component->set_gradient(BSML::Gradient::Parse(value)); }}
        };
    }
}