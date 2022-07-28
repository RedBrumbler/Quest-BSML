#include "BSML/TypeHandlers/BackgroundableHandler.hpp"
#include "Helpers/utilities.hpp"

namespace BSML {
    static BackgroundableHandler backgroundableHandler{};

    BackgroundableHandler::Base::PropMap BackgroundableHandler::get_props() const {
        auto props = Base::PropMap();
        props["background"] = std::vector<std::string>({"bg", "background"});
        props["backgroundColor"] = std::vector<std::string>({"bg-color", "background-color"});
        props["backgroundAlpha"] = std::vector<std::string>({"bg-alpha"});
        return props;
    }

    BackgroundableHandler::Base::SetterMap BackgroundableHandler::get_setters() const {
        auto setters = Base::SetterMap();
        setters["background"] = [](auto component, auto str) { 
            component->ApplyBackground(str); 
        };
        setters["backgroundColor"] = [](auto component, auto str) { 
            auto col = Utilities::ParseHTMLColorOpt(str);
            if (col.has_value()) component->ApplyColor(col.value());
        };
        setters["backgroundAlpha"] = [](auto component, auto str) {
            float v = 0;
            if (System::Single::TryParse(str, byref(v))) {
                component->ApplyAlpha(v);
            }
        };
        return setters;
    }
}