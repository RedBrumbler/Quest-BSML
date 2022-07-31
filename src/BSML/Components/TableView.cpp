#include "BSML/Components/TableView.hpp"

#include "UnityEngine/Vector2.hpp"

DEFINE_TYPE(BSML, TableView);

void BSML::TableView::ReloadData() {
    if (get_tableType() == TableType::Horizontal) {
        contentTransform->set_anchorMin({0, 0});
        contentTransform->set_anchorMax({0, 1});
    }
}