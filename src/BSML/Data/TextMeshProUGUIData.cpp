#include "BSML/Data/TextMeshProUGUIData.hpp"
#include "BSMLMacros.hpp"
#include "logging.hpp"


namespace BSML {
    TextMeshProUGUIData::TextMeshProUGUIData(const tinyxml2::XMLElement& elem) {
        GET_BSML_STRING("text", text);
        GET_BSML_FLOAT_OPT("font-size", fontSize);

        std::string fontColorStringTemp;
        GET_BSML_STRING("font-color", fontColorStringTemp);
        std::string faceColorStringTemp;
        GET_BSML_STRING("face-color", faceColorStringTemp);
        std::string outlineColorStringTemp;
        GET_BSML_STRING("outline-color", outlineColorStringTemp);

        GET_BSML_FLOAT_OPT("outline-width", outlineWidth);
        GET_BSML_BOOL("rich-text", richText);
        
        std::string fontAlignmentStringTemp;
        GET_BSML_STRING("font-align", fontAlignmentStringTemp);
        GET_BSML_STRING("align", fontAlignmentStringTemp);

        std::string overflowModeStringTemp;
        GET_BSML_STRING("overflow-mode", overflowModeStringTemp);

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
        
        textMeshProUGUI->set_text(get_text());
        if (get_fontSize().has_value()) textMeshProUGUI->set_fontSize(get_fontSize().value());
        // TODO: colors;
        if (get_fontColor().has_value()) textMeshProUGUI->set_color(get_fontColor().value());
        if (get_faceColor().has_value()) textMeshProUGUI->set_faceColor(get_faceColor().value());
        if (get_outlineColor().has_value()) textMeshProUGUI->set_outlineColor(get_outlineColor().value());
        if (get_outlineWidth().has_value()) textMeshProUGUI->set_outlineWidth(get_outlineWidth().value());
        textMeshProUGUI->set_richText(get_richText());
        // TODO: enums
        //textMeshProUGUI->set_alignment(get_fontAlignment());
        //textMeshProUGUI->set_overflowMode(get_overflowMode());
        if (get_wordWrapping().has_value()) textMeshProUGUI->set_enableWordWrapping(get_wordWrapping().value());

        // TODO: typesetting proper
        if (get_bold().value_or(false))
            textMeshProUGUI->set_text("<b>" + textMeshProUGUI->get_text() + "</b>");
        if (get_bold().value_or(true))
            textMeshProUGUI->set_text("<i>" + textMeshProUGUI->get_text() + "</i>");
        if (get_bold().value_or(false))
            textMeshProUGUI->set_text("<u>" + textMeshProUGUI->get_text() + "</u>");
        if (get_bold().value_or(false))
            textMeshProUGUI->set_text("<s>" + textMeshProUGUI->get_text() + "</s>");
    }
}