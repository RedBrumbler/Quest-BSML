#include "BSML/Tags/Settings/SliderSettingTag.hpp"
#include "logging.hpp"

#include "BSML/Components/Settings/SliderSetting.hpp"

#include "UnityEngine/GameObject.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    GameObject* sliderTemplate = nullptr;
    
    void SliderSettingTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        auto go = CreateObject(parent);
        auto slider = go->GetComponent<BSML::SliderSetting*>();
        SetHostField(host, slider);
        
        genericSettingData.Apply(slider->genericSetting, host);
        sliderSettingData.Apply(slider);
        
        CreateChildren(go->get_transform(), host);
    }

    void SliderSettingTag::parse(const tinyxml2::XMLElement& elem) {
        DEBUG("Parsing slider-setting tag");
        this->Base::parse(elem);

        sliderSettingData = SliderSettingData(elem);
    }
}