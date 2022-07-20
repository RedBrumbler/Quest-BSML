#include "BSML/Data/HorizontalOrVerticalLayoutGroupData.hpp"
#include "BSMLMacros.hpp"
#include "logging.hpp"

namespace BSML {
    HorizontalOrVerticalLayoutGroupData::HorizontalOrVerticalLayoutGroupData(const tinyxml2::XMLElement& elem) {
        GET_BSML_FLOAT_OPT("spacing", spacing);
        GET_BSML_BOOL_OPT("child-expand-width", childExpandWidth);
        GET_BSML_BOOL_OPT("child-expand-height", childExpandHeight);
        GET_BSML_BOOL_OPT("child-control-width", childControlWidth);
        GET_BSML_BOOL_OPT("child-control-height", childControlHeight);
    }

    void HorizontalOrVerticalLayoutGroupData::Apply(UnityEngine::UI::HorizontalOrVerticalLayoutGroup* horizontalOrVerticalLayoutGroup) const {
        if (!horizontalOrVerticalLayoutGroup) {
            ERROR("nullptr passed to HorizontalOrVerticalLayoutGroupData::Apply");
            return;
        }
        if (get_spacing().has_value()) horizontalOrVerticalLayoutGroup->set_spacing(get_spacing().value());
        if (get_childExpandWidth().has_value()) horizontalOrVerticalLayoutGroup->set_childForceExpandWidth(get_childExpandWidth().value());
        if (get_childExpandHeight().has_value()) horizontalOrVerticalLayoutGroup->set_childForceExpandHeight(get_childExpandHeight().value());
        if (get_childControlWidth().has_value()) horizontalOrVerticalLayoutGroup->set_childControlWidth(get_childControlWidth().value());
        if (get_childControlHeight().has_value()) horizontalOrVerticalLayoutGroup->set_childControlHeight(get_childControlHeight().value());
    }
}