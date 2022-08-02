#include "BSML/TypeHandlers/IconSegmentedControlHandler.hpp"
#include "Helpers/delegates.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

#include "HMUI/IconSegmentedControl_DataItem.hpp"

namespace BSML {
    static IconSegmentedControlHandler textSegmentedControlHandler{};

    IconSegmentedControlHandler::Base::PropMap IconSegmentedControlHandler::get_props() const {
        return {
            {"selectCell", {"select-cell", "cell-select"}},
            {"data", {"contents", "data"}}
        };
    }

    IconSegmentedControlHandler::Base::SetterMap IconSegmentedControlHandler::get_setters() const {
        return {};
    }

    void IconSegmentedControlHandler::HandleType(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) {
        auto textControl = reinterpret_cast<HMUI::IconSegmentedControl*>(componentType.component);
        auto& data = componentType.data;
        auto host = parserParams.host;

        auto dataItr = data.find("data");
        if (dataItr != data.end() && !dataItr->second.empty()) {
            auto arg = StringParseHelper(dataItr->second);
            List<HMUI::IconSegmentedControl::DataItem*>* iconData = nullptr;

            auto fieldInfo = arg.asFieldInfo(host);
            // use the 'data' value as a field name
            if (fieldInfo) iconData = il2cpp_utils::GetFieldValue<List<HMUI::IconSegmentedControl::DataItem*>*>(host, fieldInfo).value_or(nullptr);
            if (!iconData) {
                // use the 'data' value as a getter method name
                auto getterInfo = arg.asGetter(host);
                if (getterInfo) iconData = il2cpp_utils::RunMethod<List<HMUI::IconSegmentedControl::DataItem*>*>(host, getterInfo).value_or(nullptr);
            }

            if (iconData && iconData->get_Count() > 0) {
                textControl->SetData(iconData->ToArray());
            } else {
                ERROR("IconSegmentedControl needs to have at least 1 value!");
                ERROR("This means BSML could not find field '{0}' or method 'get_{0}'", arg);
            }
        }

        auto selectCellItr = data.find("selectCell");
        if (selectCellItr != data.end() && !selectCellItr->second.empty()) {
            auto arg = StringParseHelper(selectCellItr->second);
            auto methodInfo = arg.asMethodInfo(host, 2);
            if (methodInfo) {
                auto delegate = MakeSystemAction<HMUI::SegmentedControl*, int>(host, methodInfo);
                textControl->add_didSelectCellEvent(delegate);
            } else {
                ERROR("Could not find method '{}' with 2 args in class '{}::{}'", arg, host->klass->namespaze, host->klass->name);
            }
        }

        Base::HandleType(componentType, parserParams);
    }
}