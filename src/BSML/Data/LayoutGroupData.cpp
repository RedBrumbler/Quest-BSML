#include "BSML/Data/LayoutGroupData.hpp"
#include "BSMLMacros.hpp"
#include "logging.hpp"
#include <map>

std::map<std::string, UnityEngine::TextAnchor> stringToTextAnchorMap {
    {"UpperLeft", UnityEngine::TextAnchor::UpperLeft},
    {"UpperCenter", UnityEngine::TextAnchor::UpperCenter},
    {"UpperRight", UnityEngine::TextAnchor::UpperRight},
    {"MiddleLeft", UnityEngine::TextAnchor::MiddleLeft},
    {"MiddleCenter", UnityEngine::TextAnchor::MiddleCenter},
    {"MiddleRight", UnityEngine::TextAnchor::MiddleRight},
    {"LowerLeft", UnityEngine::TextAnchor::LowerLeft},
    {"LowerCenter", UnityEngine::TextAnchor::LowerCenter},
    {"LowerRight", UnityEngine::TextAnchor::LowerRight}
};

std::optional<UnityEngine::TextAnchor> stringToTextAnchor(std::string str) {
    auto itr = stringToTextAnchorMap.find(str);
    if (itr != stringToTextAnchorMap.end()) {
        return itr->second;
    }

    return std::nullopt;
}

namespace BSML {
    LayoutGroupData::LayoutGroupData(const tinyxml2::XMLElement& elem) {
        GET_BSML_INT_OPT("pad", padding);
        if (padding == 0) {
            GET_BSML_INT_OPT("pad-top", padTop);
            GET_BSML_INT_OPT("pad-bottom", padBottom);
            GET_BSML_INT_OPT("pad-left", padLeft);
            GET_BSML_INT_OPT("pad-right", padRight);
        }
        // if any of these has a value, there is padding requested, else there is no padding
        hasPadding = padding + padTop + padBottom + padLeft + padRight;

        std::string tempString;
        GET_BSML_STRING("child-align", tempString);
        childAlignment = stringToTextAnchor(tempString);
    }

    void LayoutGroupData::Apply(UnityEngine::UI::LayoutGroup* layoutGroup) const {
        if (!layoutGroup) {
            ERROR("nullptr passed to LayoutGroupData::Apply");
            return;
        }

        if (get_childAlignment().has_value()) layoutGroup->set_childAlignment(get_childAlignment().value());
        if (hasPadding) layoutGroup->set_padding(get_padding());
    }
}