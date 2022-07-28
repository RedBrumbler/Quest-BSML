#pragma once

#include "BSML/Tags/Settings/GenericSliderSettingTag.hpp"

#include "BSML/Components/Settings/SliderSetting.hpp"
#include "BSML/Data/Settings/SliderSettingData.hpp"
#include "BSML/Data/Settings/SliderSettingBaseData.hpp"

namespace BSML {
    class SliderSettingTag : public GenericSliderSettingTag<BSML::SliderSetting*> {
        private:
            using Base = GenericSliderSettingTag<BSML::SliderSetting*>;
        public:
            SliderSettingTag() : Base() {}

            virtual void Construct(UnityEngine::Transform* parent, Il2CppObject* host = nullptr) const override;
        private:
            virtual void parse(const tinyxml2::XMLElement& elem) override;
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override {
                return Base::CreateObject(parent);
            }
            
            SliderSettingBaseData sliderSettingBaseData;
            SliderSettingData sliderSettingData;
    };
}