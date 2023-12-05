#include "BSML/Components/TableView.hpp"

#include "UnityEngine/Vector2.hpp"

DEFINE_TYPE(BSML, TableView);

void BSML::TableView::ReloadData() {
    if (tableType == TableType::Horizontal) {
        contentTransform.anchorMin = {0, 0};
        contentTransform.anchorMax = {0, 1};
    }

    static auto methodInfo = il2cpp_functions::class_get_method_from_name(classof(HMUI::TableView), "ReloadData", 0);
    if (methodInfo) il2cpp_utils::RunMethod(convert(), methodInfo);
}

void BSML::TableView::DidSelectCellWithIdx(int idx) {
    static auto methodInfo = il2cpp_functions::class_get_method_from_name(classof(HMUI::TableView), "DidSelectCellWithIdx", 1);
    if (methodInfo) il2cpp_utils::RunMethod(convert(), methodInfo, idx);

    // TODO: possibly use the klass for the tableData to call a callback on that instead of registering things?
}
