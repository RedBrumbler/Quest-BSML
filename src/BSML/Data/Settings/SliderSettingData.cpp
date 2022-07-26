#include "BSML/Data/Settings/SliderSettingData.hpp"
#include "logging.hpp"
#include "internal_macros.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

namespace BSML {
    SliderSettingData::SliderSettingData(const tinyxml2::XMLElement& elem) {
        GET_BSML_FLOAT_OPT("increment", increment);
        GET_BSML_FLOAT_OPT("min", min);
        GET_BSML_FLOAT_OPT("max", max);
        GET_BSML_BOOL_OPT("integer-only", isInt);
        GET_BSML_INT_OPT("digits", digits);
    }

    void SliderSettingData::Apply(BSML::SliderSetting* sliderSetting) const {
        if (!sliderSetting) {
            ERROR("nullptr passed to SliderSettingData::Apply");
            return;
        }

        if (get_increment().has_value()) sliderSetting->increments = get_increment().value();
        if (get_min().has_value()) sliderSetting->slider->set_minValue(get_min().value());
        if (get_max().has_value()) sliderSetting->slider->set_maxValue(get_max().value());
        if (get_isInt().has_value()) sliderSetting->isInt = get_isInt().value();
        if (get_digits().has_value()) sliderSetting->digits = get_digits().value();
    }
}