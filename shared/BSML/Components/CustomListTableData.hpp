#pragma once

#include "custom-types/shared/macros.hpp"
#include "HMUI/TableView.hpp"
#include "HMUI/TableView_IDataSource.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Sprite.hpp"

#include "BoxTableCell.hpp"
#include "GlobalNamespace/LevelListTableCell.hpp"
#include "GlobalNamespace/AnnotatedBeatmapLevelCollectionCell.hpp"
#include "GlobalNamespace/SimpleTextTableCell.hpp"

#include <string>

namespace GlobalNamespace {
    using LevelPackCell = AnnotatedBeatmapLevelCollectionCell;
}

DECLARE_CLASS_CORDL(BSML, CustomCellInfo, bs_hook::Il2CppWrapperType,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(StringW, text);
        DECLARE_INSTANCE_FIELD(StringW, subText);
        DECLARE_INSTANCE_FIELD(UnityEngine::Sprite, icon);
    );

    FIELD_ACCESSOR(text);
    FIELD_ACCESSOR(subText);
    FIELD_ACCESSOR(icon);

    DECLARE_DEFAULT_CTOR();

    public:
        static CustomCellInfo construct(StringW text, StringW subText = nullptr, UnityEngine::Sprite icon = nullptr);
)

DECLARE_CLASS_CORDL_INTERFACES(BSML, CustomListTableData, UnityEngine::MonoBehaviour, classof(HMUI::TableView::IDataSource),

    DECLARE_FIELDS(
        /* pls no touchy raw listStyle if you value your sanity */
        DECLARE_INSTANCE_FIELD(int, listStyle);
        DECLARE_INSTANCE_FIELD(ListWrapper<CustomCellInfo>, data);
        DECLARE_INSTANCE_FIELD(float, cellSize);
        DECLARE_INSTANCE_FIELD(StringW, reuseIdentifier);
        DECLARE_INSTANCE_FIELD(HMUI::TableView, tableView);
        DECLARE_INSTANCE_FIELD(bool, expandCell);

        DECLARE_INSTANCE_FIELD(UnityEngine::Sprite, blackSprite);
        DECLARE_INSTANCE_FIELD(GlobalNamespace::LevelListTableCell, levelListTableCell);
        DECLARE_INSTANCE_FIELD(GlobalNamespace::LevelPackCell, levelPackCell);
        DECLARE_INSTANCE_FIELD(GlobalNamespace::SimpleTextTableCell, simpleTextTableCell);
    );

    FIELD_ACCESSOR(data);
    FIELD_ACCESSOR(cellSize);
    FIELD_ACCESSOR(reuseIdentifier);
    FIELD_ACCESSOR(tableView);
    FIELD_ACCESSOR(expandCell);
    FIELD_ACCESSOR(blackSprite);
    FIELD_ACCESSOR(levelListTableCell);
    FIELD_ACCESSOR(levelPackCell);
    FIELD_ACCESSOR(simpleTextTableCell);
    public:
        enum class ListStyle {
            List, Box, Simple
        };
        ListStyle get_listStyle();
        void set_listStyle(ListStyle value);
        __declspec(property(get=get_listStyle, put=set_listStyle)) ListStyle listStyle;

    DECLARE_INSTANCE_METHOD(GlobalNamespace::LevelListTableCell, GetTableCell);
    DECLARE_INSTANCE_METHOD(GlobalNamespace::SimpleTextTableCell, GetSimpleTextTableCell);
    DECLARE_INSTANCE_METHOD(BSML::BoxTableCell, GetBoxTableCell);

    DECLARE_OVERRIDE_METHOD(float, CellSize, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::TableView::IDataSource::CellSize>::get());
    DECLARE_OVERRIDE_METHOD(int, NumberOfCells, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::TableView::IDataSource::NumberOfCells>::get());
    DECLARE_OVERRIDE_METHOD(HMUI::TableCell, CellForIdx, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::TableView::IDataSource::CellForIdx>::get(), HMUI::TableView tableView, int idx);

    DECLARE_CTOR(ctor);

    public:
        static ListStyle stringToListStyle(const std::string& str);
        operator HMUI::TableView::IDataSource();
)
