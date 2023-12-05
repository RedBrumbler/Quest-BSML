#include "BSML/Components/CustomCellListTableData.hpp"
#include "BSML.hpp"

#include "HMUI/Touchable.hpp"
DEFINE_TYPE(BSML, CustomCellListTableData);

using namespace UnityEngine;

namespace BSML {
    void CustomCellListTableData::ctor() {
        reuseIdentifier = "BSMLCustomCellListTableData";
        cellSize = 8.5f;
        clickableCells = true;
        // this way if you make a list like <custom-cell-list data="someField"/> it'll still show cells even if you don't give it a cell template
        bsmlString = "<bg bg='round-rect-panel'><text text='Default Cell'/></bg>";
    }

    float CustomCellListTableData::CellSize() {
        return cellSize;
    }

    int CustomCellListTableData::NumberOfCells() {
        return data ? data.Count : 0;
    }

    HMUI::TableCell CustomCellListTableData::CellForIdx(HMUI::TableView tableView, int idx) {
        if (data.Count < idx) return HMUI::TableCell{nullptr};
        auto cell = BSML::CustomCellTableCell(tableView.DequeueReusableCellForIdentifier(reuseIdentifier).convert());
        auto cellData = data[idx];
        if (!cell) {
            cell = NewCellForData(cellData);
        } else {
            cell.dataObject = cellData;
            cell.Reused();
        }

        cell.reuseIdentifier = reuseIdentifier;
        cell.interactable = clickableCells;

        return cell;
    }

    BSML::CustomCellTableCell CustomCellListTableData::NewCellForData(bs_hook::Il2CppWrapperType data) {
        auto cellGo = GameObject::New_ctor("BSMLCustomCellTableCell");
        auto cell = cellGo.AddComponent<BSML::CustomCellTableCell>();

        if (clickableCells) {
            cellGo.AddComponent<HMUI::Touchable>();
            cell.interactable = true;
        }

        auto parser = parse_and_construct(bsmlString, cellGo.transform, cell);
        cell.parserParams = parser->parserParams;
        cell.dataObject = data;
        cell.SetupPostParse(*parser->parserParams);

        return cell;
    }

    CustomCellListTableData::operator HMUI::TableView::IDataSource() {
        return HMUI::TableView::IDataSource(convert());
    }
}
