#include "BSML/Data/ClickableTextData.hpp"
#include "Helpers/utilities.hpp"
#include "internal_macros.hpp"
#include "logging.hpp"

namespace BSML {
    ClickableTextData::ClickableTextData(const tinyxml2::XMLElement& elem) {
        std::string tempString;
        GET_BSML_STRING("default-color", tempString);
        defaultColor = Utilities::ParseHTMLColorOpt(tempString);

        tempString.clear();
        GET_BSML_STRING("highlight-color", tempString);
        highlightColor = Utilities::ParseHTMLColorOpt(tempString);

        GET_BSML_STRING("on-click", onClick);
    }
    
    void ClickableTextData::Apply(BSML::ClickableText* clickableText, Il2CppObject* host) const {
        if (!clickableText || !host) {
            ERROR("nullptr passed to ClickableTextData::Apply");
            return;
        }

        if (get_highlightColor().has_value()) clickableText->set_highlightColor(get_highlightColor().value());
        if (get_defaultColor().has_value()) clickableText->set_defaultColor(get_defaultColor().value());

        if (!onClick.empty()) {
            auto onClickMethodInfo = il2cpp_functions::class_get_method_from_name(host->klass, onClick.c_str(), 0);
            if (onClickMethodInfo) clickableText->onClick = [onClickMethodInfo, host](){ il2cpp_utils::RunMethod(host, onClickMethodInfo); };
        }
    }
}