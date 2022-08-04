#include "BSML/Components/CustomCellTableCell.hpp"

DEFINE_TYPE(BSML, CustomCellTableCell);

namespace BSML {
    void CustomCellTableCell::ctor() {
        selectedTags = List<UnityEngine::GameObject*>::New_ctor();
        hoveredTags = List<UnityEngine::GameObject*>::New_ctor();
        neitherTags = List<UnityEngine::GameObject*>::New_ctor();
    }
    
    void CustomCellTableCell::Reused() {
        if (dataObject) il2cpp_utils::RunMethod(dataObject, "Reused", this);
    }

    void CustomCellTableCell::SelectionDidChange(HMUI::SelectableCell::TransitionType transitionType) {
        if (get_selected() && dataObject) {
            il2cpp_utils::RunMethod(dataObject, "Select", this);
        }

        RefreshVisuals();
    }

    void CustomCellTableCell::HighlightDidChange(HMUI::SelectableCell::TransitionType transitionType) {
        RefreshVisuals();
    }

    void CustomCellTableCell::RefreshVisuals() {
        bool selected = get_selected();
        bool hovered = get_highlighted();

        for (auto go : selectedTags) go->SetActive(selected);
        for (auto go : hoveredTags) go->SetActive(hovered);
        for (auto go : neitherTags) go->SetActive(!(selected || hovered));
    }

    void CustomCellTableCell::SetupPostParse(const BSMLParserParams& parserParams) {
        auto selected = parserParams.GetObjectsWithTag("selected");
        auto hovered = parserParams.GetObjectsWithTag("hovered");
        auto neither = parserParams.GetObjectsWithTag("un-selected-un-hovered");
        
        selectedTags->EnsureCapacity(selected.size());
        for (auto go : selected) selectedTags->Add(go);
        hoveredTags->EnsureCapacity(hovered.size());
        for (auto go : hovered) hoveredTags->Add(go);
        neitherTags->EnsureCapacity(neither.size());
        for (auto go : neither) neitherTags->Add(go);

        if (dataObject) il2cpp_utils::RunMethod(dataObject, "Setup", this);
    }
}