#pragma once

#include "custom-types/shared/macros.hpp"
#include "IncDecSetting.hpp"

DECLARE_CLASS_CUSTOM(BSML, ListSetting, BSML::IncDecSetting,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(ListWrapper<bs_hook::Il2CppWrapperType>, values);
        DECLARE_INSTANCE_FIELD(int, index); /* default: 0; */
        public:
            /* set a formatter if you want to give your own format to the setting */
            std::function<StringW(bs_hook::Il2CppWrapperType)> formatter = nullptr;
    );

    FIELD_ACCESSOR(values);
    FIELD_ACCESSOR(index);
    FIELD_ACCESSOR(formatter);

    DECLARE_INSTANCE_METHOD(void, Setup);
    DECLARE_INSTANCE_METHOD(void, IncButtonPressed);
    DECLARE_INSTANCE_METHOD(void, DecButtonPressed);
    DECLARE_INSTANCE_METHOD(void, EitherPressed);
    DECLARE_INSTANCE_METHOD(void, ReceiveValue);
    DECLARE_INSTANCE_METHOD(void, ApplyValue);
    DECLARE_INSTANCE_METHOD(void, ValidateRange);
    DECLARE_INSTANCE_METHOD(void, UpdateState);

    DECLARE_INSTANCE_METHOD(bs_hook::Il2CppWrapperType, get_Value);
    DECLARE_INSTANCE_METHOD(void, set_Value, bs_hook::Il2CppWrapperType value);
    __declspec(property(get=get_Value, put=set_Value)) bs_hook::Il2CppWrapperType Value;

    DECLARE_CTOR(ctor);

)
