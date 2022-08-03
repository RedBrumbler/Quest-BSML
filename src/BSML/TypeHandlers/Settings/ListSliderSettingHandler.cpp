#include "BSML/TypeHandlers/Settings/ListSliderSettingHandler.hpp"

namespace BSML {
    static ListSliderSettingHandler listSliderSettingHandler{};

    ListSliderSettingHandler::Base::PropMap ListSliderSettingHandler::get_props() const {
        return {
            {"options", {"options", "choices"}},
            {"showButtons", {"show-buttons"}}
        };
    }

    ListSliderSettingHandler::Base::SetterMap ListSliderSettingHandler::get_setters() const {
        return {
            {"showButtons", [](auto component, auto value) { component->showButtons = value; }}
        };
    }

    void ListSliderSettingHandler::HandleType(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) {
        auto component = reinterpret_cast<ListSliderSetting*>(componentType.component);
        auto& data = componentType.data;
        auto host = parserParams.get_host();

        auto optionsItr = data.find("options");
        if (optionsItr != data.end() && !optionsItr->second.empty()) {
            auto arg = StringParseHelper(optionsItr->second);
            auto fieldInfo = arg.asFieldInfo(host);
            if (fieldInfo) {
                component->values = il2cpp_functions::field_get_value_object(fieldInfo, host);
            } else {
                auto getterInfo = arg.asGetter(host);
                if (getterInfo) {
                    auto list = il2cpp_utils::RunMethod<List<Il2CppObject*>*>(host, getterInfo);
                    if (list.has_value())
                        component->values = list.value();
                }
            }
        }

        if (!component->values || component->values->get_Count() == 0) {
            ERROR("Did not give options for dropdown list! this is required!");
        }

        Base::HandleType(componentType, parserParams);
    }
}