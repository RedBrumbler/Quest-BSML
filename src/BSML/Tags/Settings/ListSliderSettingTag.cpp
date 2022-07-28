#include "BSML/Tags/Settings/ListSliderSettingTag.hpp"
#include "logging.hpp"

#include "BSML/Components/Settings/ListSliderSetting.hpp"

#include "UnityEngine/GameObject.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLTagParser<ListSliderSettingTag> listSliderSettingTagParser({"list-slider-setting"});
    void ListSliderSettingTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        auto go = CreateObject(parent);
        auto slider = go->GetComponent<BSML::ListSliderSetting*>();
        SetHostField(host, slider);
        
        genericSettingData.Apply(slider->genericSetting, host);
        sliderSettingBaseData.Apply(slider);
        listSettingData.Apply(slider, host);
        
        CreateChildren(go->get_transform(), host);
    }

    void ListSliderSettingTag::parse(const tinyxml2::XMLElement& elem) {
        DEBUG("Parsing list-slider-setting tag");
        this->Base::parse(elem);

        sliderSettingBaseData = SliderSettingBaseData(elem);
        listSettingData = ListSettingData(elem);
    }
}