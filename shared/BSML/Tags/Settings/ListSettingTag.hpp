#pragma once


#include "BSML/Tags/Settings/IncDecSettingTag.hpp"
#include "BSML/Components/Settings/ListSetting.hpp"
#include "BSML/Data/Settings/ListSettingData.hpp"

namespace BSML {
    class ListSettingTag : public IncDecSettingTag<BSML::ListSetting*> {
    private:
        using Base = IncDecSettingTag<BSML::ListSetting*>;
    public:
        ListSettingTag() : Base() {}

        virtual void Construct(UnityEngine::Transform* parent, Il2CppObject* host = nullptr) const override;
    private:

        friend class ListSettingTagParser;
        virtual void parse(const tinyxml2::XMLElement& elem) override;
        virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override {
            return Base::CreateObject(parent);
        }

        ListSettingData listSettingData; 
    };
}