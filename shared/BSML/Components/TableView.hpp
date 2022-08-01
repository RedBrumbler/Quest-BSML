#pragma once

#include "custom-types/shared/macros.hpp"
#include "HMUI/TableView.hpp"

DECLARE_CLASS_CODEGEN(BSML, TableView, HMUI::TableView,
    DECLARE_OVERRIDE_METHOD(void, ReloadData, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::TableView::ReloadData>::get());
    DECLARE_OVERRIDE_METHOD(void, DidSelectCellWithIdx, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::TableView::DidSelectCellWithIdx>::get(), int idx);
)