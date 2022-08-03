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
        auto component = reinterpret_cast<DropdownListSetting*>(componentType.component);
        auto& data = componentType.data;
        auto host = parserParams.get_host();

        auto optionsItr = data.find("options");
        if (optionsItr != data.end() && !optionsItr->second.empty()) {
            auto arg = StringParseHelper(optionsItr->second);
            auto fieldInfo = arg.asFieldInfo(host);
            if (fieldInfo) {
                INFO("Using field");
                component->values = il2cpp_functions::field_get_value_object(fieldInfo, host);
            } else {
                auto getterInfo = arg.asGetter(host);
                INFO("Using Getter");
                if (getterInfo) {
                    INFO("Found Getter");
                    auto list = il2cpp_utils::RunMethod<List<Il2CppObject*>*>(host, getterInfo);
                    if (list.has_value()) {
                        INFO("Had Value");
                        component->values = list.value();
                    }
                }
            }
        }

        if (!component->values || component->values->get_Count() == 0) {
            ERROR("Did not give options for dropdown list! this is required!");
        }

        Base::HandleType(componentType, parserParams);
    }
}