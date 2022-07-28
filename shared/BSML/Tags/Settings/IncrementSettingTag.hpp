#pragma once

#include "BSML/Tags/Settings/IncDecSettingTag.hpp"
#include "BSML/Components/Settings/IncrementSetting.hpp"
#include "BSML/Data/Settings/IncrementSettingData.hpp"

namespace BSML {
    class IncrementSettingTag : public IncDecSettingTag<BSML::IncrementSetting*> {
    private:
        using Base = IncDecSettingTag<BSML::IncrementSetting*>;
    public:
        IncrementSettingTag() : Base() {}

        virtual void Construct(UnityEngine::Transform* parent, Il2CppObject* host = nullptr) const override;
    private:

        virtual void parse(const tinyxml2::XMLElement& elem) override;
        virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override {
            return Base::CreateObject(parent);
        }

        IncrementSettingData incrementSettingData; 
    };
}