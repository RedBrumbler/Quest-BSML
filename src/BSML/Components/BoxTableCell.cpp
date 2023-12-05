#include "BSML/Components/BoxTableCell.hpp"

#include "UnityEngine/Transform.hpp"
#include "UnityEngine/GameObject.hpp"

DEFINE_TYPE(BSML, BoxTableCell);

using namespace UnityEngine;

namespace BSML {
    void BoxTableCell::ctor() {
        selectedColor0 = {0, 0.75f, 1, 1};
        selectedColor1 = {0, 0.75f, 1, 0};
        highlightedColor0 = {0, 0.75f, 1, 1};
        highlightedColor1 = {0, 0.75f, 1, 0};
    }

    BoxTableCell BoxTableCell::Create(GlobalNamespace::AnnotatedBeatmapLevelCollectionCell prefab) {
        auto cell = Object::Instantiate(prefab);
        auto coverImage = cell.coverImage;
        auto selectionImage = cell.selectionImage;

        auto imageTransform = coverImage.transform;
        int childCount = imageTransform.childCount;
        for (int i = 0; i < childCount; i++) {
            Object::Destroy(imageTransform.GetChild(0).gameObject);
        }

        auto cellObject = cell.gameObject;
        Object::Destroy(cell);
        auto boxTableCell = cellObject.AddComponent<BoxTableCell>();
        boxTableCell.SetComponents(coverImage, selectionImage);
        return boxTableCell;
    }

    void BoxTableCell::SetComponents(HMUI::ImageView coverImage, HMUI::ImageView selectionImage) {
        this->coverImage = coverImage;
        this->selectionImage = selectionImage;
    }

    void BoxTableCell::SetData(UnityEngine::Sprite coverSprite) {
        if (coverSprite) {
            coverImage.sprite = coverSprite;
        }
    }

    void BoxTableCell::RefreshVisuals() {
        if (selected || highlighted) {
            selectionImage.enabled = true;
            selectionImage.color0 =  highlighted ? highlightedColor0 : selectedColor0;
            selectionImage.color1 =  highlighted ? highlightedColor1 : selectedColor1;
        } else {
            selectionImage.enabled = false;
        }
    }

    void BoxTableCell::SelectionDidChange(HMUI::SelectableCell::TransitionType transitionType) {
        RefreshVisuals();
    }

    void BoxTableCell::HighlightDidChange(HMUI::SelectableCell::TransitionType transitionType) {
        RefreshVisuals();
    }
}
