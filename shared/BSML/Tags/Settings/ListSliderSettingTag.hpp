#pragma once

#include "BSML/Tags/Settings/GenericSliderSettingTag.hpp"
#include "BSML/Components/Settings/ListSliderSetting.hpp"

namespace BSML {
    class ListSliderSettingTag : public GenericSliderSettingTag<BSML::ListSliderSetting*> {
        private:
            using Base = GenericSliderSettingTag<BSML::ListSliderSetting*>;
        public:
            ListSliderSettingTag() : Base() {}
        private:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override {
                return Base::CreateObject(parent);
            }
    };
}