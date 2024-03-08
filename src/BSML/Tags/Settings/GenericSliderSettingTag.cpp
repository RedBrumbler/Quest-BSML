#include "BSML/Tags/Settings/GenericSliderSettingTag.hpp"
#include "logging.hpp"

#include "BSML/Components/Settings/SliderSetting.hpp"
#include "BSML/Components/ExternalComponents.hpp"

#include "UnityEngine/Object.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/UI/ColorBlock.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Color.hpp"
#include "HMUI/CustomFormatRangeValuesSlider.hpp"
#include "BGLib/Polyglot/LocalizedTextMeshProUGUI.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    LayoutElement* get_controllersTransformTemplate() {
        static SafePtrUnity<LayoutElement> controllersTransformTemplate;
        if (!controllersTransformTemplate)
                controllersTransformTemplate = Resources::FindObjectsOfTypeAll<LayoutElement*>()->First([](auto x){ return x->get_name() == "PositionX"; });
        return controllersTransformTemplate.ptr();
    }

    UnityEngine::GameObject* GenericSliderSettingTagBase::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating SliderSettingBase");
        auto baseSetting = Object::Instantiate(get_controllersTransformTemplate(), parent, false);
        auto gameObject = baseSetting->get_gameObject();
        gameObject->set_name("BSMLSliderSetting");

        auto sliderSetting = gameObject->AddComponent(get_type()).cast<BSML::SliderSettingBase>();
        auto slider = gameObject->GetComponentInChildren<HMUI::CustomFormatRangeValuesSlider*>();
        sliderSetting->slider = slider;

        // colors to not be red
        auto& colorBlock = slider->___m_Colors;
        colorBlock.set_normalColor({0, 0, 0, 0.5});
        colorBlock.set_highlightedColor({1, 1, 1, 0.2});
        colorBlock.set_pressedColor({1, 1, 1, 0.2});
        colorBlock.set_selectedColor({1, 1, 1, 0.2});
        colorBlock.set_disabledColor({0.8, 0.8, 0.8, 0.5});

        slider->set_name("BSMLSlider");
        slider->GetComponentInChildren<TMPro::TextMeshProUGUI*>()->set_enableWordWrapping(false);
        slider->_enableDragging = true;
        auto sliderRect = slider->transform.cast<RectTransform>();
        sliderRect->set_anchorMin({1, 0});
        sliderRect->set_anchorMax({1, 1});
        sliderRect->set_sizeDelta({52, 0});
        sliderRect->set_pivot({1, 0.5f});
        sliderRect->set_anchoredPosition({0, 0});

        auto nameText = gameObject->get_transform()->Find("Title")->get_gameObject();
        Object::Destroy(nameText->GetComponent<BGLib::Polyglot::LocalizedTextMeshProUGUI*>());

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
