#include "BSML/Tags/Settings/ListSettingTag.hpp"

#include "UnityEngine/GameObject.hpp"

namespace BSML {
    void ListSettingTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        auto go = CreateObject(parent);
        auto listSetting = go->GetComponent<BSML::ListSetting*>();
        SetHostField(host, listSetting);

        valueWrapperData.Apply(listSetting->associatedValue, host);
        listSettingData.Apply(listSetting, host);

        CreateChildren(go->get_transform(), host);
    }

    void ListSettingTag::parse(const tinyxml2::XMLElement& elem) {
        Base::parse(elem);

        listSettingData = ListSettingData(elem);
    }
}