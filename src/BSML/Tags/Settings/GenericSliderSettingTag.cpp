#include "BSML/Tags/Settings/GenericSliderSettingTag.hpp"
#include "logging.hpp"

#include "BSML/Components/Settings/SliderSetting.hpp"
#include "BSML/Components/ExternalComponents.hpp"

#include "UnityEngine/Object.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "HMUI/CustomFormatRangeValuesSlider.hpp"
#include "Polyglot/LocalizedTextMeshProUGUI.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    LayoutElement* controllersTransformTemplate = nullptr;
    UnityEngine::GameObject* GenericSliderSettingTagBase::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating SliderSettingBase");
        if (!controllersTransformTemplate || !Object::IsNativeObjectAlive(controllersTransformTemplate))
                controllersTransformTemplate = Resources::FindObjectsOfTypeAll<LayoutElement*>().First([](auto x){ return x->get_name() == "PositionX"; });
        auto baseSetting = Object::Instantiate(controllersTransformTemplate, parent, false);
        auto gameObject = baseSetting->get_gameObject();
        gameObject->set_name("BSMLSliderSetting");

        auto sliderSetting = reinterpret_cast<BSML::SliderSettingBase*>(gameObject->AddComponent(get_type()));
        auto slider = gameObject->GetComponentInChildren<HMUI::CustomFormatRangeValuesSlider*>();
        sliderSetting->slider = slider;

        slider->set_name("BSMLSlider");
        slider->GetComponentInChildren<TMPro::TextMeshProUGUI*>()->set_enableWordWrapping(false);
        slider->enableDragging = true;
        auto sliderRect = reinterpret_cast<RectTransform*>(slider->get_transform());
        sliderRect->set_anchorMin({1, 0});
        sliderRect->set_anchorMax({1, 1});
        sliderRect->set_sizeDelta({52, 0});
        sliderRect->set_pivot({1, 0.5f});
        sliderRect->set_anchoredPosition({0, 0});

        auto nameText = gameObject->get_transform()->Find("Title")->get_gameObject();
        Object::Destroy(nameText->GetComponent<Polyglot::LocalizedTextMeshProUGUI*>());

        TMPro::TextMeshProUGUI* text = nameText->GetComponent<TMPro::TextMeshProUGUI*>();
        text->set_richText(true);
        text->set_text("BSMLSlider");
        text->get_rectTransform()->set_anchorMax({1, 1});

        baseSetting->set_preferredWidth(90.0f);

        auto externalComponents = gameObject->AddComponent<ExternalComponents*>();
        externalComponents->Add(text);
        
        return gameObject;
    }
}