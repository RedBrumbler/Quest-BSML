#include "BSML/Data/TextMeshProUGUIData.hpp"
#include "Helpers/utilities.hpp"
#include "internal_macros.hpp"
#include "logging.hpp"

#include <map>

std::map<std::string, TMPro::TextAlignmentOptions> stringToTextAlignmentOptions {
    {"TopLeft", TMPro::TextAlignmentOptions::TopLeft},
    {"Top", TMPro::TextAlignmentOptions::Top},
    {"TopRight", TMPro::TextAlignmentOptions::TopRight},
    {"TopJustified", TMPro::TextAlignmentOptions::TopJustified},
    {"TopFlush", TMPro::TextAlignmentOptions::TopFlush},
    {"TopGeoAligned", TMPro::TextAlignmentOptions::TopGeoAligned},
    {"Left", TMPro::TextAlignmentOptions::Left},
    {"Center", TMPro::TextAlignmentOptions::Center},
    {"Right", TMPro::TextAlignmentOptions::Right},
    {"Justified", TMPro::TextAlignmentOptions::Justified},
    {"Flush", TMPro::TextAlignmentOptions::Flush},
    {"CenterGeoAligned", TMPro::TextAlignmentOptions::CenterGeoAligned},
    {"BottomLeft", TMPro::TextAlignmentOptions::BottomLeft},
    {"Bottom", TMPro::TextAlignmentOptions::Bottom},
    {"BottomRight", TMPro::TextAlignmentOptions::BottomRight},
    {"BottomJustified", TMPro::TextAlignmentOptions::BottomJustified},
    {"BottomFlush", TMPro::TextAlignmentOptions::BottomFlush},
    {"BottomGeoAligned", TMPro::TextAlignmentOptions::BottomGeoAligned},
    {"BaselineLeft", TMPro::TextAlignmentOptions::BaselineLeft},
    {"Baseline", TMPro::TextAlignmentOptions::Baseline},
    {"BaselineRight", TMPro::TextAlignmentOptions::BaselineRight},
    {"BaselineJustified", TMPro::TextAlignmentOptions::BaselineJustified},
    {"BaselineFlush", TMPro::TextAlignmentOptions::BaselineFlush},
    {"BaselineGeoAligned", TMPro::TextAlignmentOptions::BaselineGeoAligned},
    {"MidlineLeft", TMPro::TextAlignmentOptions::MidlineLeft},
    {"Midline", TMPro::TextAlignmentOptions::Midline},
    {"MidlineRight", TMPro::TextAlignmentOptions::MidlineRight},
    {"MidlineJustified", TMPro::TextAlignmentOptions::MidlineJustified},
    {"MidlineFlush", TMPro::TextAlignmentOptions::MidlineFlush},
    {"MidlineGeoAligned", TMPro::TextAlignmentOptions::MidlineGeoAligned},
    {"CaplineLeft", TMPro::TextAlignmentOptions::CaplineLeft},
    {"Capline", TMPro::TextAlignmentOptions::Capline},
    {"CaplineRight", TMPro::TextAlignmentOptions::CaplineRight},
    {"CaplineJustified", TMPro::TextAlignmentOptions::CaplineJustified},
    {"CaplineFlush", TMPro::TextAlignmentOptions::CaplineFlush},
    {"CaplineGeoAligned", TMPro::TextAlignmentOptions::CaplineGeoAligned}
};

std::map<std::string, TMPro::TextOverflowModes> stringToOverflowModes {
    {"Overflow", TMPro::TextOverflowModes::Overflow},
    {"Ellipsis", TMPro::TextOverflowModes::Ellipsis},
    {"Masking", TMPro::TextOverflowModes::Masking},
    {"Truncate", TMPro::TextOverflowModes::Truncate},
    {"ScrollRect", TMPro::TextOverflowModes::ScrollRect},
    {"Page", TMPro::TextOverflowModes::Page},
    {"Linked", TMPro::TextOverflowModes::Linked}
};

std::optional<TMPro::TextAlignmentOptions> stringToTextAlignmentOption(std::string str) {
    auto itr = stringToTextAlignmentOptions.find(str);
    if (itr != stringToTextAlignmentOptions.end())
        return itr->second;

    return std::nullopt;
};

std::optional<TMPro::TextOverflowModes> stringToOverflowMode(std::string str) {
    auto itr = stringToOverflowModes.find(str);
    if (itr != stringToOverflowModes.end())
        return itr->second;

    return std::nullopt;
};

namespace BSML {
    TextMeshProUGUIData::TextMeshProUGUIData(const tinyxml2::XMLElement& elem) {
        GET_BSML_STRING("text", text);
        GET_BSML_STRING("label", text);
        GET_BSML_FLOAT_OPT("font-size", fontSize);

        std::string fontColorStringTemp;
        GET_BSML_STRING("font-color", fontColorStringTemp);
        fontColor = Utilities::ParseHMTMLColorOpt(fontColorStringTemp);
        std::string faceColorStringTemp;
        GET_BSML_STRING("face-color", faceColorStringTemp);
        faceColor = Utilities::ParseHMTMLColor32Opt(faceColorStringTemp);
        std::string outlineColorStringTemp;
        GET_BSML_STRING("outline-color", outlineColorStringTemp);
        faceColor = Utilities::ParseHMTMLColor32Opt(outlineColorStringTemp);
        GET_BSML_FLOAT_OPT("outline-width", outlineWidth);
        GET_BSML_BOOL("rich-text", richText);
        
        std::string fontAlignmentStringTemp;
        GET_BSML_STRING("font-align", fontAlignmentStringTemp);
        GET_BSML_STRING("align", fontAlignmentStringTemp);
        fontAlignment = stringToTextAlignmentOption(fontAlignmentStringTemp);
        std::string overflowModeStringTemp;
        GET_BSML_STRING("overflow-mode", overflowModeStringTemp);
        overflowMode = stringToOverflowMode(overflowModeStringTemp);

        GET_BSML_BOOL_OPT("word-wrapping", wordWrapping);
        GET_BSML_BOOL_OPT("bold", bold);
        GET_BSML_BOOL_OPT("italics", italics);
        GET_BSML_BOOL_OPT("underlined", underlined);
        GET_BSML_BOOL_OPT("striketrhough", strikeThrough);
        GET_BSML_BOOL_OPT("all-uppercase", allUpperCase);
    }

    void TextMeshProUGUIData::Apply(TMPro::TextMeshProUGUI* textMeshProUGUI) const {
        if (!textMeshProUGUI) {
            ERROR("nullptr passed to TextMeshProUGUIData::Apply");
            return;
        }
        
        if (get_text().has_value())textMeshProUGUI->set_text(get_text().value());
        if (get_fontSize().has_value()) textMeshProUGUI->set_fontSize(get_fontSize().value());
        if (get_fontColor().has_value()) textMeshProUGUI->set_color(get_fontColor().value());
        if (get_faceColor().has_value()) textMeshProUGUI->set_faceColor(get_faceColor().value());
        if (get_outlineColor().has_value()) textMeshProUGUI->set_outlineColor(get_outlineColor().value());
        if (get_outlineWidth().has_value()) textMeshProUGUI->set_outlineWidth(get_outlineWidth().value());
        textMeshProUGUI->set_richText(get_richText());
        if (get_fontAlignment().has_value()) textMeshProUGUI->set_alignment(get_fontAlignment().value());
        if (get_overflowMode().has_value()) textMeshProUGUI->set_overflowMode(get_overflowMode().value());
        if (get_wordWrapping().has_value()) textMeshProUGUI->set_enableWordWrapping(get_wordWrapping().value());

        std::string pre;
        std::string post;
        if (get_bold().value_or(false)) {
            pre += "<b>";
            post = "</b>" + post;
        }
        if (get_italics().value_or(true)) {
            pre += "<i>";
            post = "</i>" + post;
        }
        if (get_underlined().value_or(false)) {
            pre += "<u>";
            post = "</u>" + post;
        }
        if (get_strikeThrough().value_or(false)) {
            pre += "<s>";
            post = "</s>" + post;
        }
        if (!pre.empty())
            textMeshProUGUI->set_text(StringW(pre) + textMeshProUGUI->get_text() + StringW(post));
    }
}