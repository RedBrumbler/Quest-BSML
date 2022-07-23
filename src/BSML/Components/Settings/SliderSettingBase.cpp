#include "BSML/Components/Settings/SliderSettingBase.hpp"

#include "UnityEngine/Object.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/RectTransform.hpp"

DEFINE_TYPE(BSML, SliderSettingBase);

namespace BSML {
    void SliderSettingBase::construct() {
        this->base_ctor();
    }

    bool SliderSettingBase::get_interactable() {
        return slider ? slider->get_interactable() : false;
    }

    void SliderSettingBase::set_interactable(bool value) {
        if (slider) {
            slider->set_interactable(value);

            if (showButtons) {
                set_enableInc(value);
                set_enableDec(value);
            }
        }
    }

    void SliderSettingBase::set_enableDec(bool value) {
        if (decButton) {
            decButton->set_interactable(value);
        }
    }

    void SliderSettingBase::set_enableInc(bool value) {
        if (incButton) {
            incButton->set_interactable(value);
        }
    }

    void SliderSettingBase::Start() {
        incButton = slider->incButton;
        decButton = slider->decButton;
        
        if (!showButtons) {
            // TODO: Sprite finding stuff
            //slider.image.sprite = Utilities.FindSpriteCached("RoundRect10");
            UnityEngine::Object::Destroy(incButton->get_gameObject());
            UnityEngine::Object::Destroy(decButton->get_gameObject());
            auto transform = reinterpret_cast<UnityEngine::RectTransform*>(slider->get_transform());
            transform->set_sizeDelta({38, 0});
            auto bgRect = reinterpret_cast<UnityEngine::RectTransform*>(transform->Find("BG"));
            bgRect->set_sizeDelta({0, 6});
            auto slidingAreaRect = reinterpret_cast<UnityEngine::RectTransform*>(transform->Find("SlidingArea"));
            slidingAreaRect->set_sizeDelta({-4, -4});
        }

        auto setupInfo = il2cpp_functions::class_get_method_from_name(this->klass, "Setup", 0);
        if (setupInfo) il2cpp_utils::RunMethod(this, setupInfo);
    }
}