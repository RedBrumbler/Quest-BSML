#include "BSML/Components/Settings/ListSliderSetting.hpp"

#include "System/Action_2.hpp"
#include "UnityEngine/GameObject.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include <limits>

DEFINE_TYPE(BSML, ListSliderSetting);

namespace BSML {
    std::map<HMUI::RangeValuesTextSlider*, BSML::ListSliderSetting*> ListSliderSetting::remappers = {};
    
    void ListSliderSetting::ctor() {
        SliderSettingBase::construct();
        values = List<Il2CppObject*>::New_ctor();
    }

    void ListSliderSetting::OnDestroy() {
        remappers.erase(slider);
    }

    void ListSliderSetting::Setup() {
        if (slider) {
            remappers[slider] = this;
            
            // steps is range(max - min) divided by increments;
            int steps = values.size();
            slider->set_minValue(0);
            slider->set_maxValue(steps - 1);
            slider->set_numberOfSteps(steps);
            text = slider->get_gameObject()->GetComponentInChildren<TMPro::TextMeshProUGUI*>();
            ReceiveValue();

            using ValueDidChangeEvent_t = System::Action_2<HMUI::RangeValuesTextSlider*, float>*;
            std::function<void(HMUI::RangeValuesTextSlider*, float)> fun = std::bind(&ListSliderSetting::OnChange, this, std::placeholders::_1, std::placeholders::_2);
            auto delegate = il2cpp_utils::MakeDelegate<ValueDidChangeEvent_t>(classof(ValueDidChangeEvent_t), fun);
            slider->add_valueDidChangeEvent(delegate);
        }
    }

    void ListSliderSetting::OnChange(HMUI::RangeValuesTextSlider* _, float value) {
        auto actualValue = get_Value();
        if (genericSetting) {
            genericSetting->OnChange(actualValue);
            if (genericSetting->applyOnChange) ApplyValue();
        }
    }

    StringW ListSliderSetting::TextForValue(Il2CppObject* value) {
        if (formatter)
            return formatter(value);
        else {
            return value ? value->ToString() : "NULL";
        }
    }


    void ListSliderSetting::ReceiveValue() {
        if (!genericSetting) return;
        set_Value(genericSetting->GetValue<Il2CppObject*>());
    }

    void ListSliderSetting::ApplyValue() {
        if (!genericSetting) return;
        genericSetting->SetValue(get_Value());
    }
    
    Il2CppObject* ListSliderSetting::get_Value() {
        if (values.size() > 0)
            return values[get_index()];
        return nullptr;
    }

    void ListSliderSetting::set_Value(Il2CppObject* value) {
        int index = 0;
        for (auto& v : values) {
            // if both are the same, or v has a value and Equals the value
            if ((v == value) || (v && il2cpp_utils::RunMethod<bool>(v, "Equals", value).value_or(false)))
                break;
            index++;
        }

        if (index == values.size())
            index = values.size() - 1;
        
        slider->set_value(index);
    }

    int ListSliderSetting::get_index() {
        return slider ? slider->get_value() : 0;
    }
}