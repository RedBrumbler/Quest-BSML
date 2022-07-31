#include "BSML/TypeHandlers/Settings/BaseSettingHandler.hpp"
#include "BSML/GenericSettingWrapper.hpp"

namespace BSML {
    static BaseSettingHandler baseSettingHandler{};

    int BaseSettingHandler::get_priority() const { return 10; }
    BaseSettingHandler::Base::PropMap BaseSettingHandler::get_props() const {
        return {
            {"onChange", {"on-change"}},
            {"value", {"value"}},
            {"applyOnChange", {"apply-on-change"}}
        };
    }

    BaseSettingHandler::Base::SetterMap BaseSettingHandler::get_setters() const {
        return {};
    }

    void BaseSettingHandler::HandleType(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) {
        auto component = componentType.component;
        auto& data = componentType.data;
        auto host = parserParams.host;

        auto genericSettings = il2cpp_utils::GetFieldValue<GenericSettingWrapper*>(component, "genericSetting").value_or(nullptr);
        if (!genericSettings) {
            ERROR("Type {}::{} did not have a 'genericSetting' field", component->klass->namespaze, component->klass->name);
            return;
        }

        genericSettings->host = host;
        
        auto applyOnChangeItr = data.find("applyOnChange");
        if (applyOnChangeItr != data.end()) {
            auto arg = StringParseHelper(applyOnChangeItr->second);
            genericSettings->applyOnChange = arg.tryParseBool().value_or(true);
        }

        auto valueItr = data.find("value");
        if (valueItr != data.end() && !valueItr->second.empty()) {
            auto arg = StringParseHelper(valueItr->second);
            genericSettings->valueInfo = arg.asFieldInfo(host);
            if (!genericSettings->valueInfo) {
                genericSettings->getterInfo = arg.asGetter(host);
                genericSettings->setterInfo = arg.asSetter(host);
            }
        }

        auto onChangeItr = data.find("onChange");
        if (onChangeItr != data.end() && !onChangeItr->second.empty()) {
            auto arg = StringParseHelper(onChangeItr->second);
            genericSettings->onChangeInfo = arg.asMethodInfo(host, 1);
            if (!genericSettings->onChangeInfo) genericSettings->onChangeInfo = arg.asMethodInfo(host, 0);
        }

        Base::HandleType(componentType, parserParams);
    }

    void BaseSettingHandler::HandleTypeAfterChildren(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) {
        auto baseSetupMethodInfo = StringParseHelper("BaseSetup").asMethodInfo(componentType.component, 0);
        if (baseSetupMethodInfo) il2cpp_utils::RunMethod(componentType.component, baseSetupMethodInfo);
        
        auto setupMethodInfo = StringParseHelper("Setup").asMethodInfo(componentType.component, 0);
        if (setupMethodInfo) il2cpp_utils::RunMethod(componentType.component, setupMethodInfo);
        
        Base::HandleTypeAfterChildren(componentType, parserParams);
    }

}