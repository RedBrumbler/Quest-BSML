#pragma once

#include "custom-types/shared/macros.hpp"
#include "../Parsing/BSMLParserParams.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/SelectableCell.hpp"
#include "HMUI/TableCell.hpp"

DECLARE_CLASS_CORDL(BSML, CustomCellTableCell, HMUI::TableCell,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(bs_hook::Il2CppWrapperType, dataObject);
        DECLARE_INSTANCE_FIELD(ListWrapper<UnityEngine::GameObject>, selectedTags);
        DECLARE_INSTANCE_FIELD(ListWrapper<UnityEngine::GameObject>, hoveredTags);
        DECLARE_INSTANCE_FIELD(ListWrapper<UnityEngine::GameObject>, neitherTags);

        public:
            std::shared_ptr<BSMLParserParams> parserParams;
    );

    FIELD_ACCESSOR(dataObject);
    FIELD_ACCESSOR(selectedTags);
    FIELD_ACCESSOR(hoveredTags);
    FIELD_ACCESSOR(neitherTags);
    FIELD_ACCESSOR(parserParams);

    DECLARE_OVERRIDE_METHOD(void, SelectionDidChange, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::SelectableCell::SelectionDidChange>::get(), HMUI::SelectableCell::TransitionType transitionType);
    DECLARE_OVERRIDE_METHOD(void, HighlightDidChange, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::SelectableCell::HighlightDidChange>::get(), HMUI::SelectableCell::TransitionType transitionType);
    DECLARE_INSTANCE_METHOD(void, RefreshVisuals);
    DECLARE_INSTANCE_METHOD(void, Reused);

    DECLARE_CTOR(ctor);
    DECLARE_SIMPLE_DTOR();

    public:
        void SetupPostParse(const BSMLParserParams& parserParams);
)
