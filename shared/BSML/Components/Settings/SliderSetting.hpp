#pragma once

#include "SliderSettingBase.hpp"
#include "HMUI/CustomFormatRangeValuesSlider.hpp"
#include <map>

DECLARE_CLASS_CUSTOM(BSML, SliderSetting, BSML::SliderSettingBase,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(bool, isInt);        /* default: false;                                      */
        DECLARE_INSTANCE_FIELD(float, increments);  /* default: 1;                                          */
        DECLARE_INSTANCE_FIELD(float, lastValue);   /* default: -std::numeric_limits<float>::infinity();    */
        DECLARE_INSTANCE_FIELD(int, digits);        /* default: 2;                                          */
        public:
            std::function<void(float)> onChange = nullptr;
            std::function<StringW(float)> formatter = nullptr;
    );

    FIELD_ACCESSOR(isInt);
    FIELD_ACCESSOR(increments);
    FIELD_ACCESSOR(lastValue);
    FIELD_ACCESSOR(digits);
    FIELD_ACCESSOR(onChange);
    FIELD_ACCESSOR(formatter);

    DECLARE_INSTANCE_METHOD(float, get_Value);
    DECLARE_INSTANCE_METHOD(void, set_Value, float value);
    __declspec(property(get=get_Value, put=set_Value)) float Value;

    DECLARE_INSTANCE_METHOD(void, Setup);
    DECLARE_INSTANCE_METHOD(void, OnDestroy);
    DECLARE_INSTANCE_METHOD(void, OnChange, HMUI::RangeValuesTextSlider _, float value);
    DECLARE_INSTANCE_METHOD(void, ApplyValue);
    DECLARE_INSTANCE_METHOD(void, ReceiveValue);
    DECLARE_INSTANCE_METHOD(StringW, TextForValue, float value);

    DECLARE_CTOR(ctor);
    public:
        static std::map<HMUI::RangeValuesTextSlider, BSML::SliderSetting> remappers;
)
