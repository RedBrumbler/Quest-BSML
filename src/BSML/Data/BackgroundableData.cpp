#include "BSML/Data/BackgroundableData.hpp"
#include "Helpers/utilities.hpp"
#include "internal_macros.hpp"
#include "logging.hpp"

#include "HMUI/ImageView.hpp"
#include "UnityEngine/GameObject.hpp"

namespace BSML {
    BackgroundableData::BackgroundableData(const tinyxml2::XMLElement& elem) {
        GET_BSML_STRING("background", background);
        GET_BSML_STRING("bg", background);
        
        std::string tempString;
        GET_BSML_STRING("background-color", tempString);
        GET_BSML_STRING("bg-color", tempString);
        backgroundColor = Utilities::ParseHTMLColorOpt(tempString);

        GET_BSML_STRING("background-color0", tempString);
        GET_BSML_STRING("bg-color0", tempString);
        backgroundColor0 = Utilities::ParseHTMLColorOpt(tempString);

        GET_BSML_STRING("background-color1", tempString);
        GET_BSML_STRING("bg-color1", tempString);
        backgroundColor1 = Utilities::ParseHTMLColorOpt(tempString);

    }

    void BackgroundableData::Apply(BSML::Backgroundable* backgroundable) const {
        if (!backgroundable) {
            ERROR("nullptr passed to BackgroundableData::Apply");
            return;
        }

        if (!get_background().empty()) {
            backgroundable->ApplyBackground(get_background());
        } else {
            return;
        }

        if (get_backgroundColor().has_value()) {
            backgroundable->ApplyColor(get_backgroundColor().value());
        } else if (get_backgroundColor0().has_value() && get_backgroundColor1().has_value()) {
            backgroundable->ApplyGradient(get_backgroundColor0().value(), get_backgroundColor1().value());
        }
    }
}