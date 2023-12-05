#include "BSML/TypeHandlers/Settings/DropDownListSettingHandler.hpp"

namespace BSML {
    static DropdownListSettingHandler dropdownListSettingHandler{};

    DropdownListSettingHandler::Base::PropMap DropdownListSettingHandler::get_props() const {
        return {
            {"options", {"options", "choices"}}
        };
    }

    DropdownListSettingHandler::Base::SetterMap DropdownListSettingHandler::get_setters() const {
        return {};
    }

    void DropdownListSettingHandler::HandleType(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) {
        DropdownListSetting component {componentType.component.convert()};
        auto& data = componentType.data;

        auto optionsItr = data.find("options");
        if (optionsItr != data.end() && !optionsItr->second.empty()) {
            auto val = parserParams.TryGetValue(optionsItr->second);
            if (val) component.values = val->GetValue<List<bs_hook::Il2CppWrapperType>*>();
        }

        if (!component.values || component.values.Length() == 0) {
            ERROR("Did not give options for dropdown list! this is required!");
        }

        Base::HandleType(componentType, parserParams);
    }
}
