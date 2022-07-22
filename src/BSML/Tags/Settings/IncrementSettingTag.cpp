#include "BSML/Tags/Settings/IncrementSettingTag.hpp"

#include "UnityEngine/GameObject.hpp"

namespace BSML {
    void IncrementSettingTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        auto go = CreateObject(parent);
        auto IncrementSetting = go->GetComponent<BSML::IncrementSetting*>();
        SetHostField(host, IncrementSetting);

        valueWrapperData.Apply(IncrementSetting->associatedValue, host);
        incrementSettingData.Apply(IncrementSetting);

        CreateChildren(go->get_transform(), host);
    }

    void IncrementSettingTag::parse(const tinyxml2::XMLElement& elem) {
        Base::parse(elem);

        incrementSettingData = IncrementSettingData(elem);
    }
}