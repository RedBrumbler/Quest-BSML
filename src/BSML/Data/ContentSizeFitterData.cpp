#include "BSML/Data/ContentSizeFitterData.hpp"
#include "BSMLMacros.hpp"
#include "logging.hpp"
#include <map>

std::map<std::string, UnityEngine::UI::ContentSizeFitter::FitMode> stringToFitModeMap {
    {"Unconstrained", UnityEngine::UI::ContentSizeFitter::FitMode::Unconstrained},
    {"MinSize", UnityEngine::UI::ContentSizeFitter::FitMode::MinSize},
    {"PreferredSize", UnityEngine::UI::ContentSizeFitter::FitMode::PreferredSize}
};

std::optional<UnityEngine::UI::ContentSizeFitter::FitMode> stringToFitMode(std::string str) {
    auto itr = stringToFitModeMap.find(str);
    if (itr != stringToFitModeMap.end()) {
        return itr->second;
    }

    return std::nullopt;
}

namespace BSML {
    ContentSizeFitterData::ContentSizeFitterData(const tinyxml2::XMLElement& elem) {
        std::string horizontalFitStringTemp;
        GET_BSML_STRING("horizontal-fit", horizontalFitStringTemp);
        std::string verticalFitStringTemp;
        GET_BSML_STRING("vertical-fit", verticalFitStringTemp);

        horizontalFit = stringToFitMode(horizontalFitStringTemp);
        verticalFit = stringToFitMode(verticalFitStringTemp);
    }

    void ContentSizeFitterData::Apply(UnityEngine::UI::ContentSizeFitter* contentSizeFitter) const {
        if (!contentSizeFitter) {
            ERROR("nullptr passed to ContentSizeFitterData::Apply");
            return;
        }

        if (get_horizontalFit()) contentSizeFitter->set_horizontalFit(get_horizontalFit().value());
        if (get_verticalFit()) contentSizeFitter->set_verticalFit(get_verticalFit().value());
    }
}