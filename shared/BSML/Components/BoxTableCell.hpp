#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/Color.hpp"
#include "HMUI/TableCell.hpp"
#include "HMUI/ImageView.hpp"
#include "HMUI/SelectableCell.hpp"
#include "GlobalNamespace/AnnotatedBeatmapLevelCollectionCell.hpp"

DECLARE_CLASS_CODEGEN(BSML, BoxTableCell, HMUI::TableCell,
    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, coverImage);
    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, selectionImage);
    DECLARE_INSTANCE_FIELD(UnityEngine::Color, selectedColor0);
    DECLARE_INSTANCE_FIELD(UnityEngine::Color, selectedColor1);
    DECLARE_INSTANCE_FIELD(UnityEngine::Color, highlightedColor0);
    DECLARE_INSTANCE_FIELD(UnityEngine::Color, highlightedColor1);

    DECLARE_INSTANCE_METHOD(void, SetComponents, HMUI::ImageView* coverImage, HMUI::ImageView* selectionImage);
    DECLARE_INSTANCE_METHOD(void, SetData, UnityEngine::Sprite* coverSprite);
    DECLARE_INSTANCE_METHOD(void, RefreshVisuals);

    DECLARE_OVERRIDE_METHOD(void, SelectionDidChange, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::SelectableCell::SelectionDidChange>::get(), HMUI::SelectableCell::TransitionType transitionType);
    DECLARE_OVERRIDE_METHOD(void, HighlightDidChange, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::SelectableCell::HighlightDidChange>::get(), HMUI::SelectableCell::TransitionType transitionType);

    DECLARE_CTOR(ctor);
    public:
        static BoxTableCell* Create(GlobalNamespace::AnnotatedBeatmapLevelCollectionCell* prefab);

)