#include "BSML/Components/CustomListTableData.hpp"
#include "Helpers/utilities.hpp"

#include "GlobalNamespace/LayoutWidthLimiter.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include <map>

DEFINE_TYPE(BSML, CustomListTableData);
DEFINE_TYPE(BSML, CustomCellInfo);

using namespace UnityEngine;

namespace BSML {
    void CustomListTableData::ctor() {
        data = List<CustomCellInfo*>::New_ctor();
        cellSize = 8.5f;
        reuseIdentifier = "BSMLListTableCell";

        blackSprite = Utilities::LoadSpriteFromTexture(Texture2D::get_blackTexture(), 1);
    }

    HMUI::TableCell* CustomListTableData::CellForIdx(HMUI::TableView* tableView, int idx) {
        auto cellInfo = data[idx];
        if (!cellInfo) return nullptr; 
        switch (get_listStyle()) {
            case ListStyle::List: {
                auto tableCell = GetTableCell();
                auto nameText = tableCell->songNameText;
                auto authorText = tableCell->songAuthorText;

                tableCell->songBpmText->get_gameObject()->SetActive(false);
                tableCell->songDurationText->get_gameObject()->SetActive(false);
                tableCell->favoritesBadgeImage->get_gameObject()->SetActive(false);

                // new stuff in 1.28.0 that needs to be disabled
                // TODO: make it a feature to make this usable?
                tableCell->updatedBadgeGo->SetActive(false);
                tableCell->promoBadgeGo->SetActive(false);
                tableCell->promoBackgroundGo->SetActive(false);
                tableCell->layoutWidthLimiter->set_limitWidth(false);

                static ConstString bpmIcon("BpmIcon");
                tableCell->get_transform()->Find(bpmIcon)->get_gameObject()->SetActive(false);

                if (expandCell) {
                    nameText->get_rectTransform()->set_anchorMax({2, 0.5f});
                    authorText->get_rectTransform()->set_anchorMax({2, 0.5f});
                }

                nameText->set_text(cellInfo->text);
                authorText->set_text(cellInfo->subText ? cellInfo->subText : "");
                tableCell->coverImage->set_sprite(cellInfo->icon ? cellInfo->icon : blackSprite);
                return tableCell;
            }
            case ListStyle::Box: {
                auto tableCell = GetBoxTableCell();
                tableCell->SetData(cellInfo->icon == nullptr ? blackSprite : cellInfo->icon);
                return tableCell;
            }
            case ListStyle::Simple: {
                auto tableCell = GetSimpleTextTableCell();
                tableCell->text->set_richText(true);
                tableCell->text->set_enableWordWrapping(true);
                tableCell->set_text(cellInfo->text);
                return tableCell;
            }
        }

        return nullptr;
    }

    GlobalNamespace::LevelListTableCell* CustomListTableData::GetTableCell() {
        auto tableCell = reinterpret_cast<GlobalNamespace::LevelListTableCell*>(tableView->DequeueReusableCellForIdentifier(reuseIdentifier));

        if (!tableCell) {
            if (!levelListTableCell || !levelListTableCell->m_CachedPtr.m_value) {
                levelListTableCell = Resources::FindObjectsOfTypeAll<GlobalNamespace::LevelListTableCell*>().FirstOrDefault([](auto x){ return x->get_name() == "LevelListTableCell"; });
            }

            tableCell = Object::Instantiate(levelListTableCell);
        }

        tableCell->notOwned = false;
        tableCell->set_reuseIdentifier(reuseIdentifier);
        return tableCell;
    }

    GlobalNamespace::SimpleTextTableCell* CustomListTableData::GetSimpleTextTableCell() {
        auto tableCell = reinterpret_cast<GlobalNamespace::SimpleTextTableCell*>(tableView->DequeueReusableCellForIdentifier(reuseIdentifier));
        
        if (!tableCell) {
            if (!simpleTextTableCell || !simpleTextTableCell->m_CachedPtr.m_value) {
                simpleTextTableCell = Resources::FindObjectsOfTypeAll<GlobalNamespace::SimpleTextTableCell*>().FirstOrDefault([](auto x){ return x->get_name() == "SimpleTextTableCell"; });
            }

            tableCell = Object::Instantiate(simpleTextTableCell);
        }

        tableCell->set_reuseIdentifier(reuseIdentifier);
        return tableCell;
    }

    BSML::BoxTableCell* CustomListTableData::GetBoxTableCell() {
        auto tableCell = reinterpret_cast<BSML::BoxTableCell*>(tableView->DequeueReusableCellForIdentifier(reuseIdentifier));

        if (!tableCell) {
            if (!levelPackCell || !levelPackCell->m_CachedPtr.m_value) {
                levelPackCell = Resources::FindObjectsOfTypeAll<GlobalNamespace::LevelPackCell*>().FirstOrDefault([](auto x){ return x->get_name() == "AnnotatedBeatmapLevelCollectionCell"; });
            }
            tableCell = BSML::BoxTableCell::Create(levelPackCell);
        }
        
        tableCell->set_reuseIdentifier(reuseIdentifier);
        return tableCell;
    }


    CustomListTableData::ListStyle CustomListTableData::get_listStyle() {
        return static_cast<CustomListTableData::ListStyle>(listStyle);
    }

    float CustomListTableData::CellSize() {
        return cellSize;
    }

    int CustomListTableData::NumberOfCells() {
        return data ? data->get_Count() : 0;
    }

    void CustomListTableData::set_listStyle(CustomListTableData::ListStyle value) {
        listStyle = static_cast<int>(value);

        switch(value) {
            default: [[fallthrough]];
            case ListStyle::List:
                cellSize = 8.5f;
                break;
            case ListStyle::Box:
                cellSize = 30 + (5 * (tableView->get_tableType() == HMUI::TableView::TableType::Horizontal));
                break;
            case ListStyle::Simple:
                cellSize = 8.0f;
                break;
        }
    }

    HMUI::TableView::IDataSource* CustomListTableData::i_IDataSource() { return reinterpret_cast<HMUI::TableView::IDataSource*>(this); }

    CustomCellInfo* CustomCellInfo::construct(StringW text, StringW subText, UnityEngine::Sprite* icon) {
        auto instance = CustomCellInfo::New_ctor();
        instance->text = text;
        instance->subText = subText;
        instance->icon = icon;
        return instance;
    }

    CustomListTableData::ListStyle CustomListTableData::stringToListStyle(const std::string& str) {
        static std::map<std::string, CustomListTableData::ListStyle> stringToListStyleMap {
            { "List", CustomListTableData::ListStyle::List },
            { "Box", CustomListTableData::ListStyle::Box },
            { "Simple", CustomListTableData::ListStyle::Simple }
        };

        auto itr = stringToListStyleMap.find(str);
        if (itr == stringToListStyleMap.end()) return CustomListTableData::ListStyle::List;
        return itr->second;
    }

}