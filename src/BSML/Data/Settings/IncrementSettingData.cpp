#include "BSML/Data/Settings/IncrementSettingData.hpp"
#include "logging.hpp"
#include "internal_macros.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

namespace BSML {
    IncrementSettingData::IncrementSettingData(const tinyxml2::XMLElement& elem) {
        GET_BSML_FLOAT_OPT("increment", increment);
        GET_BSML_FLOAT_OPT("min", min);
        GET_BSML_FLOAT_OPT("max", max);
        GET_BSML_BOOL_OPT("integer-only", isInt);
        GET_BSML_INT_OPT("digits", digits);
    }

    void IncrementSettingData::Apply(BSML::IncrementSetting* incrementSetting) const {
        if (!incrementSetting) {
            ERROR("nullptr passed to IncrementSettingData::Apply");
            return;
        }

        if (get_increment().has_value()) incrementSetting->increments = get_increment().value();
        if (get_min().has_value()) incrementSetting->minValue = get_min().value();
        if (get_max().has_value()) incrementSetting->maxValue = get_max().value();
        if (get_isInt().has_value()) incrementSetting->isInt = get_isInt().value();
        if (get_digits().has_value()) incrementSetting->digits = get_digits().value();
    }
}