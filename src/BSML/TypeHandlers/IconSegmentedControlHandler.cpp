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
        auto host = parserParams.get_host();

        auto dataItr = data.find("data");
        if (dataItr != data.end() && !dataItr->second.empty()) {
            auto val = parserParams.TryGetValue(dataItr->second);
            List<HMUI::IconSegmentedControl::DataItem*>* iconData = val ? val->GetValue<List<HMUI::IconSegmentedControl::DataItem*>*>() : nullptr;
            static auto dataKlass = classof(List<HMUI::IconSegmentedControl::DataItem*>*);
            if (iconData && il2cpp_functions::class_is_assignable_from(iconData->klass, dataKlass) && iconData->get_Count() > 0) {
                textControl->SetData(iconData->ToArray());
            } else if (iconData && !il2cpp_functions::class_is_assignable_from(iconData->klass, dataKlass)) {
                ERROR("{}::{} is not assignable from {}::{}", iconData->klass->namespaze, iconData->klass->name, dataKlass->namespaze, dataKlass->name);
            } else {
                ERROR("IconSegmentedControl needs to have at least 1 value!");
                ERROR("This means BSML could not find value '{0}'", dataItr->second);
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