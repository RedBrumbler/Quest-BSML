#pragma once

#include "custom-types/shared/macros.hpp"
#include "IncDecSetting.hpp"

DECLARE_CLASS_CUSTOM(BSML, IncrementSetting, BSML::IncDecSetting,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(float, currentValue);    /* default: 0.0f                                        */
        DECLARE_INSTANCE_FIELD(bool, isInt);            /* default: false                                       */
        DECLARE_INSTANCE_FIELD(int, digits);            /* default: 2;                                          */
        DECLARE_INSTANCE_FIELD(float, minValue);        /* default: -std::numeric_limits<float>::infinity();    */
        DECLARE_INSTANCE_FIELD(float, maxValue);        /* default: std::numeric_limits<float>::infinity();     */
        DECLARE_INSTANCE_FIELD(float, increments);      /* default: 1.0f;                                       */

        public:
            std::function<void(float)> onChange = nullptr;
            /* set a formatter if you want to give your own format to the setting */
            std::function<StringW(float)> formatter = nullptr;
    );

    FIELD_ACCESSOR(currentValue);
    FIELD_ACCESSOR(isInt);
    FIELD_ACCESSOR(digits);
    FIELD_ACCESSOR(minValue);
    FIELD_ACCESSOR(maxValue);
    FIELD_ACCESSOR(increments);
    FIELD_ACCESSOR(onChange);
    FIELD_ACCESSOR(formatter);

    DECLARE_INSTANCE_METHOD(void, Setup);
    DECLARE_INSTANCE_METHOD(void, IncButtonPressed);
    DECLARE_INSTANCE_METHOD(void, DecButtonPressed);
    DECLARE_INSTANCE_METHOD(void, EitherPressed);
    DECLARE_INSTANCE_METHOD(void, ReceiveValue);
    DECLARE_INSTANCE_METHOD(void, ApplyValue);
    DECLARE_INSTANCE_METHOD(void, ValidateRange);
    DECLARE_INSTANCE_METHOD(void, UpdateState);
    DECLARE_INSTANCE_METHOD(StringW, TextForValue, float value);
    DECLARE_INSTANCE_METHOD(int, ConvertToInt, float value);
    DECLARE_INSTANCE_METHOD(float, get_Value);
    DECLARE_INSTANCE_METHOD(void, set_Value, float value);
    __declspec(property(get=get_Value, put=set_Value)) float Value;

    DECLARE_CTOR(ctor);

)
