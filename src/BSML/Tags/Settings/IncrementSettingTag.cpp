#include "BSML/Tags/Settings/IncrementSettingTag.hpp"

#include "UnityEngine/GameObject.hpp"

namespace BSML {
    static BSMLTagParser<IncrementSettingTag> incrementSettingTagParser({"increment-setting"});
    void IncrementSettingTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        auto go = CreateObject(parent);
        auto incrementSetting = go->GetComponent<BSML::IncrementSetting*>();
        SetHostField(host, incrementSetting);

        genericSettingData.Apply(incrementSetting->genericSetting, host);
        incrementSettingData.Apply(incrementSetting);

        CreateChildren(go->get_transform(), host);
    }

    void IncrementSettingTag::parse(const tinyxml2::XMLElement& elem) {
        Base::parse(elem);

        incrementSettingData = IncrementSettingData(elem);
    }
}