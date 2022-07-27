#include "BSML/Data/GridLayoutGroupData.hpp"
#include "internal_macros.hpp"
#include "logging.hpp"

extern UnityEngine::Vector2 merge(const UnityEngine::Vector2& original, const std::optional<float>& x, const std::optional<float>& y);

namespace BSML {
    GridLayoutGroupData::GridLayoutGroupData(const tinyxml2::XMLElement& elem) {
        GET_BSML_FLOAT_OPT("cell-size-x", cellSizeX);
        GET_BSML_FLOAT_OPT("cell-size-y", cellSizeY);
        GET_BSML_FLOAT_OPT("spacing-x", spacingX);
        GET_BSML_FLOAT_OPT("spacing-y", spacingY);
    }

    void GridLayoutGroupData::Apply(UnityEngine::UI::GridLayoutGroup* gridLayoutGroup) const {
        if (!gridLayoutGroup) {
            ERROR("nullptr passed to GridLayoutGroupData::Apply");
            return;
        }
        gridLayoutGroup->set_cellSize(merge(gridLayoutGroup->get_cellSize(), get_cellSizeX(), get_cellSizeY()));
        gridLayoutGroup->set_spacing(merge(gridLayoutGroup->get_spacing(), get_spacingX(), get_spacingY()));
    }
}