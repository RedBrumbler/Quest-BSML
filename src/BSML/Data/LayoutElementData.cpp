#include "BSML/Data/LayoutElementData.hpp"
#include "BSMLMacros.hpp"
#include "logging.hpp"

namespace BSML {
    LayoutElementData::LayoutElementData(const tinyxml2::XMLElement& elem) {
        GET_BSML_BOOL_OPT("ignore-layout", ignoreLayout);
        GET_BSML_FLOAT_OPT("preferred-width", preferredWidth);
        GET_BSML_FLOAT_OPT("pref-width", preferredWidth);
        GET_BSML_FLOAT_OPT("preferred-height", preferredHeight);
        GET_BSML_FLOAT_OPT("pref-height", preferredHeight);
        GET_BSML_FLOAT_OPT("min-width", minimumWidth);
        GET_BSML_FLOAT_OPT("min-height", minimumHeight);
    }

    void LayoutElementData::Apply(UnityEngine::UI::LayoutElement* layoutElement) const {
        if (!layoutElement) {
            ERROR("nullptr passed to LayoutElementData::Apply");
            return;
        }
        
        if (get_ignoreLayout().has_value()) layoutElement->set_ignoreLayout(get_ignoreLayout().value());
        if (get_preferredWidth().has_value()) layoutElement->set_preferredWidth(get_preferredWidth().value());
        if (get_preferredHeight().has_value()) layoutElement->set_preferredHeight(get_preferredHeight().value());
        if (get_minimumWidth().has_value()) layoutElement->set_minWidth(get_minimumWidth().value());
        if (get_minimumHeight().has_value()) layoutElement->set_minHeight(get_minimumHeight().value());
    }
}