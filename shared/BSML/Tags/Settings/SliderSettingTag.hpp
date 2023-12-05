#pragma once

#include "../Settings/GenericSliderSettingTag.hpp"
#include "../../Components/Settings/SliderSetting.hpp"

namespace BSML {
    class SliderSettingTag : public GenericSliderSettingTag<BSML::SliderSetting> {
        private:
            using Base = GenericSliderSettingTag<BSML::SliderSetting>;
        public:
            SliderSettingTag() : Base() {}
        private:
            virtual UnityEngine::GameObject CreateObject(UnityEngine::Transform parent) const override;
                return Base::CreateObject(parent);
            }
    };
}
