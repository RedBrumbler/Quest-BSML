#pragma once

#include "custom-types/shared/macros.hpp"
#include "CustomCellTableCell.hpp"
#include "HMUI/TableView.hpp"
#include "HMUI/TableCell.hpp"
#include "HMUI/TableView_IDataSource.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Sprite.hpp"

#include <string>

DECLARE_CLASS_CODEGEN_INTERFACES(BSML, CustomCellListTableData, UnityEngine::MonoBehaviour, classof(HMUI::TableView::IDataSource*),
    DECLARE_INSTANCE_FIELD(ListWrapper<Il2CppObject*>, data);
    DECLARE_INSTANCE_FIELD(float, cellSize);
    DECLARE_INSTANCE_FIELD(bool, clickableCells);
    DECLARE_INSTANCE_FIELD(StringW, reuseIdentifier);
    DECLARE_INSTANCE_FIELD(HMUI::TableView*, tableView);

    DECLARE_OVERRIDE_METHOD(float, CellSize, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::TableView::IDataSource::CellSize>::get());
    DECLARE_OVERRIDE_METHOD(int, NumberOfCells, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::TableView::IDataSource::NumberOfCells>::get());
    DECLARE_OVERRIDE_METHOD(HMUI::TableCell*, CellForIdx, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::TableView::IDataSource::CellForIdx>::get(), HMUI::TableView* tableView, int idx);
    DECLARE_INSTANCE_METHOD(CustomCellTableCell*, NewCellForData, Il2CppObject* data);

    DECLARE_CTOR(ctor);

    public:
        std::string bsmlString;
        HMUI::TableView::IDataSource* i_IDataSource();
)
