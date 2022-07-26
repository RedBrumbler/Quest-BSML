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
    }

    void BackgroundableData::Apply(QuestUI::Backgroundable* backgroundable) const {
        if (!backgroundable) {
            ERROR("nullptr passed to BackgroundableData::Apply");
            return;
        }

        if (get_backgroundColor().has_value()) {
            auto color = get_backgroundColor().value();
            backgroundable->ApplyBackgroundWithAlpha(get_background(), color.a);

            auto imageView = backgroundable->get_gameObject()->GetComponentInChildren<HMUI::ImageView*>();
            if (imageView) imageView->set_color(color);
        } else {
            backgroundable->ApplyBackground(get_background());
        }
    }
}