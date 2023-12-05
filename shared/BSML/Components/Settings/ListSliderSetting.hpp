#pragma once

#include "custom-types/shared/macros.hpp"
#include "SliderSettingBase.hpp"
#include <map>

DECLARE_CLASS_CUSTOM(BSML, ListSliderSetting, BSML::SliderSettingBase,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(ListWrapper<bs_hook::Il2CppWrapperType>, values);
        public:
            /* set a formatter if you want to give your own format to the setting */
            std::function<StringW(bs_hook::Il2CppWrapperType)> formatter = nullptr;
    );

    FIELD_ACCESSOR(values);
    FIELD_ACCESSOR(formatter);

    DECLARE_INSTANCE_METHOD(void, Setup);
    DECLARE_INSTANCE_METHOD(void, OnDestroy);
    DECLARE_INSTANCE_METHOD(void, ReceiveValue);
    DECLARE_INSTANCE_METHOD(void, ApplyValue);

    DECLARE_INSTANCE_METHOD(bs_hook::Il2CppWrapperType, get_Value);
    DECLARE_INSTANCE_METHOD(void, set_Value, bs_hook::Il2CppWrapperType value);
    __declspec(property(get=get_Value, put=set_Value)) bs_hook::Il2CppWrapperType Value;
    DECLARE_INSTANCE_METHOD(int, get_index);
    __declspec(property(get=get_index)) int index;

    DECLARE_INSTANCE_METHOD(void, OnChange, HMUI::RangeValuesTextSlider _, float value);
    DECLARE_INSTANCE_METHOD(StringW, TextForValue, bs_hook::Il2CppWrapperType value);

    DECLARE_CTOR(ctor);

    public:
        static std::map<HMUI::RangeValuesTextSlider, BSML::ListSliderSetting> remappers;
)
