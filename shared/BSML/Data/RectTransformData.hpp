#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/RectTransform.hpp"

namespace BSML {
    class RectTransformData {
        public:
            RectTransformData() {};
            explicit RectTransformData(const tinyxml2::XMLElement& elem);

            UnityEngine::Vector2 get_anchoredMinimum() const { return {anchorMinX.value_or(0), anchorMinY.value_or(0)}; }
            auto get_anchoredMinimum_exists() const { return anchorMinX.has_value() && anchorMinY.has_value(); }
            auto get_anchoredMinimumX() const { return anchorMinX; }
            auto get_anchoredMinimumY() const { return anchorMinY; }
            UnityEngine::Vector2 get_anchoredMaximum() const { return {anchorMaxX.value_or(1), anchorMaxY.value_or(1)}; }
            auto get_anchoredMaximum_exists() const { return anchorMaxX.has_value() && anchorMaxY.has_value(); }
            auto get_anchoredMaximumX() const { return anchorMaxX; }
            auto get_anchoredMaximumY() const { return anchorMaxY; }
            UnityEngine::Vector2 get_anchoredPosition() const { return {anchorPosX.value_or(0), anchorPosY.value_or(0)}; }
            auto get_anchoredPosition_exists() const { return anchorPosX.has_value() && anchorPosY.has_value(); }
            auto get_anchoredPositionX() const { return anchorPosX; }
            auto get_anchoredPositionY() const { return anchorPosY; }
            UnityEngine::Vector2 get_sizeDelta() const { return {sizeDeltaX.value_or(0), sizeDeltaY.value_or(0)}; }
            auto get_sizeDelta_exists() const { return sizeDeltaX.has_value() && sizeDeltaY.has_value(); }
            auto get_sizeDeltaX() const { return sizeDeltaX; }
            auto get_sizeDeltaY() const { return sizeDeltaY; }
            UnityEngine::Vector2 get_pivot() const { return {pivotX.value_or(0), pivotY.value_or(0)}; }
            auto get_pivot_exists() const { return pivotX.has_value() && pivotY.has_value(); }
            auto get_pivotX() const { return pivotX; }
            auto get_pivotY() const { return pivotY; }
            std::string_view get_hoverHint() const { return hoverHint; }
            auto get_active() const { return active; }
            
            void Apply(UnityEngine::RectTransform* rectTransform) const;
        private:
            std::optional<float> anchorMinX;
            std::optional<float> anchorMinY;
            std::optional<float> anchorMaxX;
            std::optional<float> anchorMaxY;
            std::optional<float> anchorPosX;
            std::optional<float> anchorPosY;
            std::optional<float> sizeDeltaX;
            std::optional<float> sizeDeltaY;
            std::optional<float> pivotX;
            std::optional<float> pivotY;

            std::string hoverHint;
            bool active = true;
    };
}