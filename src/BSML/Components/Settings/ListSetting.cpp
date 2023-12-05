#include "BSML/Components/Settings/ListSetting.hpp"

DEFINE_TYPE(BSML, ListSetting);

namespace BSML {
    void ListSetting::ctor() {
        IncDecSetting::construct();
        values = List<bs_hook::Il2CppWrapperType>::New_ctor();
        index = 0;
    }

    void ListSetting::Setup() {
        ReceiveValue();
        if (values.size() > 0)
            UpdateState();
    }

    void ListSetting::IncButtonPressed() {
        index++;
        EitherPressed();
    }

    void ListSetting::DecButtonPressed() {
        index--;
        EitherPressed();
    }

    void ListSetting::EitherPressed() {
        UpdateState();

        if (genericSetting) {
            genericSetting.OnChange(values[index]);
            if (genericSetting.applyOnChange) ApplyValue();
        }
    }

    void ListSetting::ReceiveValue() {
        if (!genericSetting) return;
        Value = genericSetting.GetValue<bs_hook::Il2CppWrapperType>();
    }

    void ListSetting::ApplyValue() {
        if (!genericSetting) return;
        genericSetting.SetValue(Value);
    }

    void ListSetting::ValidateRange() {
        if (index >= values.size())
            index = values.size() - 1;
        if (index < 0)
            index = 0;
    }

    void ListSetting::UpdateState() {
        if (values.size() > 0) {
            set_enableDec(index > 0);
            set_enableInc(index < values.size() - 1);
            StringW text;
            if (formatter)
                text = formatter(values[index]);
            else {
                auto value = values[index];
                if (value) {
                    text = value.ToString();
                } else {
                    text = "NULL";
                }
            }
            this->text = text;
        } else {
            enableDec = false;
            enableInc = false;
            this->text = "No values";
        }
    }

    bs_hook::Il2CppWrapperType ListSetting::get_Value() {
        ValidateRange();
        if (values.size() == 0) return bs_hook::Il2CppWrapperType(nullptr);
        return values[index];
    }

    void ListSetting::set_Value(bs_hook::Il2CppWrapperType value) {
        index = 0;
        for (auto& v : values) {
            // if both are the same, or v has a value and Equals the value
            if ((v == value) || (v && il2cpp_utils::RunMethod<bool>(static_cast<Il2CppObject*>(v), "Equals", static_cast<Il2CppObject*>(value)).value_or(false)))
                break;
            index++;
        }

        if (index == values.size())
            index = values.size() - 1;

        UpdateState();
    }
}
