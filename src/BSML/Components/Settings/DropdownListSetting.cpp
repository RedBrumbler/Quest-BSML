#include "BSML/Components/Settings/DropdownListSetting.hpp"
#include "Helpers/delegates.hpp"
#include "logging.hpp"

#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/GameObject.hpp"
#include "System/Action_2.hpp"

DEFINE_TYPE(BSML, DropdownListSetting);

namespace BSML {
    void DropdownListSetting::ctor() {
        genericSetting = GenericSettingWrapper::New_ctor();
        values = List<bs_hook::Il2CppWrapperType>::New_ctor();
        index = 0;
        formatter = nullptr;
    }

    bool DropdownListSetting::get_interactable() {
        return dropdown ? dropdown.button.interactable : false;
    }

    void DropdownListSetting::set_interactable(bool value) {
        if (dropdown) dropdown.button.interactable = value;
    }

    void DropdownListSetting::Setup() {
        if (dropdown) {
            std::function<void(HMUI::DropdownWithTableView, int)> fun = [self= *this](auto _1, auto _2){ self.OnSelectIndex(_1, _2); };
            auto delegate = MakeSystemAction(fun);
            dropdown.add_didSelectCellWithIdxEvent(delegate);
        }

        ReceiveValue();
        UpdateChoices();
        gameObject.SetActive(true);
    }

    void DropdownListSetting::UpdateChoices() {
        auto texts = List<StringW>::New_ctor();
        texts.EnsureCapacity(values.Count);
        bool formatted = formatter != nullptr;
        for (auto v : values) {
            if (!v) texts.Add("NULL");
            if (formatted) [[unlikely]] {
                texts.Add(formatter(v));
            } else [[likely]] {
                texts.Add(System::Object(v.convert()).ToString());
            }
        }

        dropdown.SetTexts(texts);
    }

    void DropdownListSetting::ValidateRange() {
        if (index >= values.size())
            index = values.size() - 1;

        if (index < 0)
            index = 0;
    }

    void DropdownListSetting::UpdateState() {
        if (dropdown && dropdown.text) {
            auto value = Value;
            if (value) {
                dropdown.text.text = (formatter ? formatter(value) : System::Object(value).ToString() );
            } else {
                dropdown.text.text = "NULL";
            }
        }
    }

    void DropdownListSetting::OnSelectIndex(HMUI::DropdownWithTableView tableView, int index) {
        this->index = index;
        UpdateState();
        if (genericSetting) {
            auto v = Value;
            genericSetting.OnChange(v);
            if (onChange) onChange(v);
            if (genericSetting.applyOnChange) ApplyValue();
        }
    }

    void DropdownListSetting::ReceiveValue() {
        if (!genericSetting) return;
        Value = genericSetting.GetValue<bs_hook::Il2CppWrapperType>();
    }

    void DropdownListSetting::ApplyValue() {
        if (genericSetting)
            genericSetting.SetValue(Value);
    }

    bs_hook::Il2CppWrapperType DropdownListSetting::get_Value() {
        ValidateRange();
        return values[index];
    }

    void DropdownListSetting::set_Value(bs_hook::Il2CppWrapperType value) {
        index = 0;
        for (auto& v : values) {
            // if both are the same, or v has a value and Equals the value
            if ((v == value) || (v && il2cpp_utils::RunMethod<bool>(static_cast<Il2CppObject*>(v), "Equals", static_cast<Il2CppObject*>(value)).value_or(false)))
                break;
            index++;
        }

        if (index == values.size())
            index = values.size() - 1;

        dropdown.SelectCellWithIdx(index);

        UpdateState();
    }
}
