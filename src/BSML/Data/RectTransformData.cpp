#include "BSML/Data/RectTransformData.hpp"
#include "internal_macros.hpp"
#include "logging.hpp"

#include "UnityEngine/GameObject.hpp"
#include "questui/shared/BeatSaberUI.hpp"

UnityEngine::Vector2 merge(const UnityEngine::Vector2& original, const std::optional<float>& x, const std::optional<float>& y) {
    return {x.value_or(original.x), y.value_or(original.y)};
}

namespace BSML {
    RectTransformData::RectTransformData(const tinyxml2::XMLElement& elem) {
        GET_BSML_FLOAT_OPT("anchor-min-x", anchorMinX);
        GET_BSML_FLOAT_OPT("anchor-min-y", anchorMinY);
        GET_BSML_FLOAT_OPT("anchor-max-x", anchorMaxX);
        GET_BSML_FLOAT_OPT("anchor-max-y", anchorMaxY);
        GET_BSML_FLOAT_OPT("anchor-pos-x", anchorPosX);
        GET_BSML_FLOAT_OPT("anchor-pos-y", anchorPosY);
        GET_BSML_FLOAT_OPT("size-delta-x", sizeDeltaX);
        GET_BSML_FLOAT_OPT("size-delta-y", sizeDeltaY);
        GET_BSML_FLOAT_OPT("pivot-x", pivotX);
        GET_BSML_FLOAT_OPT("pivot-y", pivotY);

        GET_BSML_STRING("hover-hint", hoverHint);
        GET_BSML_BOOL("active", active);
    }

    void RectTransformData::Apply(UnityEngine::RectTransform* rectTransform) const {
        if (!rectTransform) {
            ERROR("nullptr passed to RectTransformData::Apply");
            return;
        }

        if (get_anchoredMinimum_exists()) rectTransform->set_anchorMin(merge(rectTransform->get_anchorMin(), get_anchoredMinimumX(), get_anchoredMinimumY()));
        if (get_anchoredMaximum_exists()) rectTransform->set_anchorMax(merge(rectTransform->get_anchorMax(), get_anchoredMaximumX(), get_anchoredMaximumY()));
        if (get_anchoredPosition_exists()) rectTransform->set_anchoredPosition(merge(rectTransform->get_anchoredPosition(), get_anchoredPositionX(), get_anchoredPositionY()));
        if (get_sizeDelta_exists()) rectTransform->set_sizeDelta(merge(rectTransform->get_sizeDelta(), get_sizeDeltaX(), get_sizeDeltaY()));
        if (get_pivot_exists()) rectTransform->set_pivot(merge(rectTransform->get_pivot(), get_pivotX(), get_pivotY()));

        if (!hoverHint.empty()) {
            QuestUI::BeatSaberUI::AddHoverHint(rectTransform->get_gameObject(), hoverHint);
        }

        rectTransform->get_gameObject()->SetActive(active);
    }
}