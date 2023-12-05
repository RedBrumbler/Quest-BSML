#include "BSML/Components/Settings/ListSliderSetting.hpp"
#include "Helpers/delegates.hpp"

#include "System/Action_2.hpp"
#include "UnityEngine/GameObject.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include <limits>

DEFINE_TYPE(BSML, ListSliderSetting);

namespace BSML {
    std::map<HMUI::RangeValuesTextSlider*, BSML::ListSliderSetting*> ListSliderSetting::remappers = {};

    void ListSliderSetting::ctor() {
        SliderSettingBase::construct();
        values = List<bs_hook::Il2CppWrapperType>::New_ctor();
    }

    void ListSliderSetting::OnDestroy() {
        remappers.erase(slider);
    }

    void ListSliderSetting::Setup() {
        if (slider) {
            remappers[slider] = this;

            // steps is range(max - min) divided by increments;
            int steps = values.size();
            slider.minValue = 0;
            slider.maxValue = steps - 1;
            slider.numberOfSteps = steps;
            text = slider.gameObject.GetComponentInChildren<TMPro::TextMeshProUGUI>();
            ReceiveValue();

            auto onChangeInfo = il2cpp_functions::class_get_method_from_name(il2cpp_functions::object_get_class(*this), "OnChange", 2);
            auto delegate = MakeSystemAction<HMUI::RangeValuesTextSlider, float>(*this, onChangeInfo);
            slider.add_valueDidChangeEvent(delegate);
        }
    }

    void ListSliderSetting::OnChange(HMUI::RangeValuesTextSlider _, float value) {
        auto actualValue = get_Value();
        if (genericSetting) {
            genericSetting.OnChange(actualValue);
            if (genericSetting.applyOnChange) ApplyValue();
        }
    }

    StringW ListSliderSetting::TextForValue(bs_hook::Il2CppWrapperType value) {
        if (formatter)
            return formatter(value);
        else {
            return value ? value.ToString() : "NULL";
        }
    }


    void ListSliderSetting::ReceiveValue() {
        if (!genericSetting) return;
        Value = genericSetting.GetValue<bs_hook::Il2CppWrapperType>();
    }

    void ListSliderSetting::ApplyValue() {
        if (!genericSetting) return;
        genericSetting.SetValue(Value);
    }

    bs_hook::Il2CppWrapperType ListSliderSetting::get_Value() {
        if (values.size() > 0)
            return values[index];
        return nullptr;
    }

    void ListSliderSetting::set_Value(bs_hook::Il2CppWrapperType value) {
        int index = 0;
        for (auto& v : values) {
            // if both are the same, or v has a value and Equals the value
            if ((v == value) || (v && il2cpp_utils::RunMethod<bool>(static_cast<Il2CppObject*>(v), "Equals", static_cast<Il2CppObject*>(value)).value_or(false)))
                break;
            index++;
        }

        if (index == values.size())
            index = values.size() - 1;

        slider.value = index;
    }

    int ListSliderSetting::get_index() {
        return slider ? slider.value : 0;
    }
}
