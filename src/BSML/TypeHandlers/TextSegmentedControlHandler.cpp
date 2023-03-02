#include "BSML/TypeHandlers/TextSegmentedControlHandler.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "Helpers/delegates.hpp"

namespace BSML {
    static TextSegmentedControlHandler textSegmentedControlHandler{};

    TextSegmentedControlHandler::Base::PropMap TextSegmentedControlHandler::get_props() const {
        return {
            {"selectCell", {"select-cell", "cell-select"}},
            {"data", {"contents", "data"}}
        };
    }

    TextSegmentedControlHandler::Base::SetterMap TextSegmentedControlHandler::get_setters() const {
        return {};
    }

    void TextSegmentedControlHandler::HandleType(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) {
        auto textControl = reinterpret_cast<HMUI::TextSegmentedControl*>(componentType.component);
        auto& data = componentType.data;

        auto dataItr = data.find("data");
        if (dataItr != data.end() && !dataItr->second.empty()) {
            auto val = parserParams.TryGetValue(dataItr->second);
            ListWrapper<StringW> texts = List<StringW>::New_ctor();
            static auto dataKlass = classof(List<Il2CppObject*>*);
            static auto stringDataKlass = classof(List<Il2CppString*>*);

            List<Il2CppObject*>* data = val ? val->GetValue<List<Il2CppObject*>*>() : nullptr;

            if (data) {
                if (il2cpp_functions::class_is_assignable_from(data->klass, stringDataKlass)) {
                    // it's already a list of strings :)
                    ListWrapper<StringW> strings = reinterpret_cast<List<StringW>*>(data);
                    for (auto str : strings) texts->Add(str);
                } else if (il2cpp_functions::class_is_assignable_from(data->klass, dataKlass)) {
                    // it's a list of objects, use ToString
                    ListWrapper<Il2CppObject*> objects = data;
                    for (auto obj : objects) texts->Add(obj ? obj->ToString() : StringW(""));
                }
            } else if (data && !il2cpp_functions::class_is_assignable_from(data->klass, dataKlass)) {
                ERROR("klass {}::{} is not assignable from {}::{}", data->klass->namespaze, data->klass->name, dataKlass->namespaze, dataKlass->name);
            } else {
                ERROR("Could not find value {}", dataItr->second);
            }

            if (texts->get_Count() > 0) {
                textControl->SetTexts(texts->i_IReadOnlyList_1_T());
            } else {
                ERROR("TextSegmentedControl needs to have at least 1 value!");
                ERROR("This means BSML could not find field '{0}' or method 'get_{0}'", dataItr->second);
            }
        }

        auto selectCellItr = data.find("selectCell");
        if (selectCellItr != data.end() && !selectCellItr->second.empty()) {
            auto action = parserParams.TryGetAction(selectCellItr->second);
            if (action) textControl->add_didSelectCellEvent(action->GetSystemAction<HMUI::SegmentedControl*, int>());
            else ERROR("Action '{}' could not be found", selectCellItr->second);
        }

        Base::HandleType(componentType, parserParams);
    }
}