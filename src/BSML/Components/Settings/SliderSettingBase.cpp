#include "BSML/Components/Settings/SliderSettingBase.hpp"
#include "Helpers/utilities.hpp"

#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/RectTransform.hpp"

DEFINE_TYPE(BSML, SliderSettingBase);

namespace BSML {
    void SliderSettingBase::construct() {
        genericSetting = GenericSettingWrapper::New_ctor();
    }

    bool SliderSettingBase::get_interactable() {
        return slider ? slider.interactable : false;
    }

    void SliderSettingBase::set_interactable(bool value) {
        if (slider) {
            slider.interactable = value;

            if (showButtons) {
                enableInc = value;
                enableDec = value;
            }
        }
    }

    void SliderSettingBase::set_enableDec(bool value) {
        if (decButton) {
            decButton.interactable = value;
        }
    }

    void SliderSettingBase::set_enableInc(bool value) {
        if (incButton) {
            incButton.interactable = value;
        }
    }

    void SliderSettingBase::BaseSetup() {
        incButton = slider.incButton;
        decButton = slider.decButton;

        if (!showButtons) {
            slider.image.sprite = Utilities::FindSpriteCached("RoundRect10");
            UnityEngine::Object::Destroy(incButton.gameObject);
            UnityEngine::Object::Destroy(decButton.gameObject);
            UnityEngine::RectTransform transform {slider.transform.convert()};
            transform.sizeDelta = {38, 0};
            UnityEngine::RectTransform bgRect {transform.Find("BG").convert()};
            bgRect.sizeDelta = {0, 6};
            UnityEngine::RectTransform slidingAreaRect {transform.Find("SlidingArea").convert()};
            slidingAreaRect.sizeDelta = {-4, -4};
        }
    }
}
