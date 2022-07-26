#include "BSML/Components/Settings/SliderSetting.hpp"
#include "logging.hpp"

#include "System/Action_2.hpp"
#include "UnityEngine/GameObject.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

#include <limits>

DEFINE_TYPE(BSML, SliderSetting);

namespace BSML {
    std::map<HMUI::RangeValuesTextSlider*, BSML::SliderSetting*> SliderSetting::remappers = {};

    void SliderSetting::ctor() {
        SliderSettingBase::construct();
        isInt = false;
        increments = 1;
        lastValue = -std::numeric_limits<float>::infinity();
        digits = 2;
    }
    void SliderSetting::OnDestroy() {
        remappers.erase(slider);
    }

    float SliderSetting::get_Value() {
        return slider ? slider->get_value() : 0.0f;
    }

    void SliderSetting::set_Value(float value) {
        if (slider) {
            slider->set_value(value);
        }
    }

    void SliderSetting::Setup() {
        if (slider) {
            remappers[slider] = this;
            text = slider->get_gameObject()->GetComponentInChildren<TMPro::TextMeshProUGUI*>();
            
            // steps is range(max - min) divided by increments;
            int steps = (slider->get_maxValue() - slider->get_minValue()) / increments;
            slider->set_numberOfSteps(steps + 1);
            ReceiveValue();

            using ValueDidChangeEvent_t = System::Action_2<HMUI::RangeValuesTextSlider*, float>*;
            std::function<void(HMUI::RangeValuesTextSlider*, float)> fun = std::bind(&SliderSetting::OnChange, this, std::placeholders::_1, std::placeholders::_2);
            auto delegate = il2cpp_utils::MakeDelegate<ValueDidChangeEvent_t>(classof(ValueDidChangeEvent_t), fun);
            slider->add_valueDidChangeEvent(delegate);
        }
    }
    
    void SliderSetting::OnChange(HMUI::RangeValuesTextSlider* _, float value) {
        if (isInt)
            value = (int)value;

        if (lastValue == value)
            return;

        lastValue = value;

        if (genericSetting) {
            genericSetting->OnChange<int>(value);
            if (genericSetting->applyOnChange) ApplyValue();
        }
    }

    void SliderSetting::ApplyValue() {
        if (!genericSetting) return;

        if (genericSetting) {
            if (isInt) {
                genericSetting->SetValue<int>(slider->get_value());
            } else {
                genericSetting->SetValue(slider->get_value());
            }
        }
    }

    void SliderSetting::ReceiveValue() {
        if (!genericSetting) return;
        set_Value(genericSetting->GetValue<float>());
    }

    StringW SliderSetting::TextForValue(float value) {
        // since the formatter can't differentiate between int and float, we just call it
        if (formatter) return formatter(value);

        if (isInt) {
            return fmt::format("{}", (int)value);
        } else {
            return fmt::format("{:.{}f}", value, digits);
        }
    }
}