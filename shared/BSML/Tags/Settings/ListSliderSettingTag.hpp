#pragma once

#include "BSML/Tags/Settings/GenericSliderSettingTag.hpp"

#include "BSML/Components/Settings/ListSliderSetting.hpp"

namespace BSML {
    class ListSliderSettingTag : public GenericSliderSettingTag<BSML::ListSliderSetting*> {
        private:
            using Base = GenericSliderSettingTag<BSML::ListSliderSetting*>;
        public:
            ListSliderSettingTag() : Base() {}

            virtual void Construct(UnityEngine::Transform* parent, Il2CppObject* host = nullptr) const override;
        private:
            virtual void parse(const tinyxml2::XMLElement& elem) override;
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override {
                return Base::CreateObject(parent);
            }
    };
}