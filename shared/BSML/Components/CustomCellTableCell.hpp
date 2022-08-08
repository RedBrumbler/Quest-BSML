#pragma once

#include "custom-types/shared/macros.hpp"
#include "../Parsing/BSMLParserParams.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/SelectableCell.hpp"
#include "HMUI/TableCell.hpp"

DECLARE_CLASS_CODEGEN(BSML, CustomCellTableCell, HMUI::TableCell,
    DECLARE_INSTANCE_FIELD(Il2CppObject*, dataObject);
    DECLARE_INSTANCE_FIELD(ListWrapper<UnityEngine::GameObject*>, selectedTags);
    DECLARE_INSTANCE_FIELD(ListWrapper<UnityEngine::GameObject*>, hoveredTags);
    DECLARE_INSTANCE_FIELD(ListWrapper<UnityEngine::GameObject*>, neitherTags);

    DECLARE_OVERRIDE_METHOD(void, SelectionDidChange, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::SelectableCell::SelectionDidChange>::get(), HMUI::SelectableCell::TransitionType transitionType);
    DECLARE_OVERRIDE_METHOD(void, HighlightDidChange, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::SelectableCell::HighlightDidChange>::get(), HMUI::SelectableCell::TransitionType transitionType);
    DECLARE_INSTANCE_METHOD(void, RefreshVisuals);
    DECLARE_INSTANCE_METHOD(void, Reused);

    DECLARE_CTOR(ctor);
    DECLARE_SIMPLE_DTOR();
    
    public:
        std::shared_ptr<BSMLParserParams> parserParams;
        void SetupPostParse(const BSMLParserParams& parserParams);
)