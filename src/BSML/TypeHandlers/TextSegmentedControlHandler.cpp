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
        auto host = parserParams.get_host();

        auto dataItr = data.find("data");
        if (dataItr != data.end() && !dataItr->second.empty()) {
            auto arg = StringParseHelper(dataItr->second);
            ListWrapper<StringW> texts = List<StringW>::New_ctor();

            static auto stringklass = classof(Il2CppString*);

            auto fieldInfo = arg.asFieldInfo(host);
            auto fieldOpt = il2cpp_utils::GetFieldValue<List<Il2CppObject*>*>(host, fieldInfo);
            // use the 'data' value as a field name
            if (fieldOpt.has_value()) {
                ListWrapper<Il2CppObject*> list = fieldOpt.value();
                texts->EnsureCapacity(list->get_Count());
                for (auto v : list) {
                    if (v->klass == stringklass)
                        texts->Add(reinterpret_cast<Il2CppString*>(v));
                    else
                        texts->Add(v->ToString());
                }
            } else {
                // use the 'data' value as a getter method name
                auto getterInfo = arg.asGetter(host);
                auto getOpt = il2cpp_utils::RunMethod<List<Il2CppObject*>*>(host, getterInfo);
                if (getOpt.has_value()) {
                    ListWrapper<Il2CppObject*> list = getOpt.value();
                    texts->EnsureCapacity(list->get_Count());
                    for (auto v : list) {
                        if (v->klass == stringklass)
                            texts->Add(reinterpret_cast<Il2CppString*>(v));
                        else
                            texts->Add(v->ToString());
                    }
                }
            }

            if (texts->get_Count() > 0) {
                textControl->SetTexts(texts->i_IReadOnlyList_1_T());
            } else {
                ERROR("TextSegmentedControl needs to have at least 1 value!");
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