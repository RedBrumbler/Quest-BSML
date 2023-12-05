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
    LayoutElement get_controllersTransformTemplate() {
        static SafePtrUnity<LayoutElement> controllersTransformTemplate;
        if (!controllersTransformTemplate)
            controllersTransformTemplate = Resources::FindObjectsOfTypeAll<LayoutElement>().First([](auto x){ return x.name == "PositionX"; });
        return LayoutElement(controllersTransformTemplate.ptr());
    }

    UnityEngine::GameObject GenericSliderSettingTagBase::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating SliderSettingBase");
        auto baseSetting = Object::Instantiate(get_controllersTransformTemplate(), parent, false);
        auto gameObject = baseSetting.gameObject;
        gameObject.name = "BSMLSliderSetting";

        BSML::SliderSettingBase sliderSetting {gameObject.AddComponent(get_type())};
        auto slider = gameObject.GetComponentInChildren<HMUI::CustomFormatRangeValuesSlider>();
        sliderSetting.slider = slider;

        // colors to not be red
        auto& colorBlock = slider.m_Colors;
        colorBlock.normalColor = {0, 0, 0, 0.5};
        colorBlock.highlightedColor = {1, 1, 1, 0.2};
        colorBlock.pressedColor = {1, 1, 1, 0.2};
        colorBlock.selectedColor = {1, 1, 1, 0.2};
        colorBlock.disabledColor = {0.8, 0.8, 0.8, 0.5};

        slider.name = "BSMLSlider";
        slider.GetComponentInChildren<TMPro::TextMeshProUGUI>().enableWordWrapping = false;
        slider._enableDragging = true;
        RectTransform sliderRect {slider.transform.convert()};
        sliderRect.anchorMin = {1, 0};
        sliderRect.anchorMax = {1, 1};
        sliderRect.sizeDelta = {52, 0};
        sliderRect.pivot = {1, 0.5f};
        sliderRect.anchoredPosition = {0, 0};

        auto nameText = gameObject.transform.Find("Title").gameObject;
        Object::Destroy(nameText.GetComponent<Polyglot::LocalizedTextMeshProUGUI>());

        auto text = nameText.GetComponent<TMPro::TextMeshProUGUI>();
        text.richText = true;
        text.text = "BSMLSlider";
        text.rectTransform.anchorMax = {1, 1};

        baseSetting.preferredWidth = 90.0f;

        auto externalComponents = gameObject.AddComponent<ExternalComponents>();
        externalComponents.Add(text);

        return gameObject;
    }
}
