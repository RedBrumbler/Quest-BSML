#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/Color32.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "TMPro/TextAlignmentOptions.hpp"
#include "TMPro/TextOverflowModes.hpp"

namespace BSML {
    class TextMeshProUGUIData {
        public:
            TextMeshProUGUIData() {};
            explicit TextMeshProUGUIData(const tinyxml2::XMLElement& elem);

            auto get_text() const { return text; }
            auto get_fontSize() const { return fontSize; }
            auto get_fontColor() const { return fontColor; }
            auto get_faceColor() const { return faceColor; }
            auto get_outlineColor() const { return outlineColor; }
            auto get_outlineWidth() const { return outlineWidth; }
            auto get_richText() const { return richText; }
            auto get_fontAlignment() const { return fontAlignment; }
            auto get_overflowMode() const { return overflowMode; }
            auto get_wordWrapping() const { return wordWrapping; }
            auto get_bold() const { return bold; }
            auto get_italics() const { return italics; }
            auto get_underlined() const { return underlined; }
            auto get_strikeThrough() const { return strikeThrough; }
            auto get_allUpperCase() const { return allUpperCase; }

            void Apply(TMPro::TextMeshProUGUI* textMeshProUGUI) const;
        private:
            std::optional<std::string> text;
            std::optional<float> fontSize;
            std::optional<UnityEngine::Color> fontColor;
            std::optional<UnityEngine::Color32> faceColor;
            std::optional<UnityEngine::Color32> outlineColor;
            std::optional<float> outlineWidth = 0.0f;
            bool richText = true;
            std::optional<TMPro::TextAlignmentOptions> fontAlignment;
            std::optional<TMPro::TextOverflowModes> overflowMode;
            std::optional<bool> wordWrapping;
            std::optional<bool> bold;
            std::optional<bool> italics;
            std::optional<bool> underlined;
            std::optional<bool> strikeThrough;
            std::optional<bool> allUpperCase;
    };
}