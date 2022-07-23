#include "BSML/Data/Settings/SliderSettingBaseData.hpp"
#include "logging.hpp"
#include "internal_macros.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

namespace BSML {
    SliderSettingBaseData::SliderSettingBaseData(const tinyxml2::XMLElement& elem) {
        GET_BSML_BOOL_OPT("show-buttons", showButtons);
    }

    void SliderSettingBaseData::Apply(BSML::SliderSettingBase* sliderSetting) const {
        if (!sliderSetting) {
            ERROR("nullptr passed to SliderSettingBaseData::Apply");
            return;
        }

        if (get_showButtons().has_value()) sliderSetting->showButtons = get_showButtons().value();
    }
}