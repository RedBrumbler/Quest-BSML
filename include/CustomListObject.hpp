#pragma once

#include "custom-types/shared/macros.hpp"
#include "BSML/Components/CustomCellTableCell.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

DECLARE_CLASS_CORDL(BSML, CustomListObject, bs_hook::Il2CppWrapperType,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(CustomCellTableCell, cell);
        DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI, cellText);
    );

    FIELD_ACCESSOR(cell);
    FIELD_ACCESSOR(cellText);

    DECLARE_INSTANCE_METHOD(void, Select, CustomCellTableCell cell);
    DECLARE_INSTANCE_METHOD(void, Setup, CustomCellTableCell cell);
    DECLARE_INSTANCE_METHOD(void, Reused, CustomCellTableCell cell);

    public:
        DECLARE_DEFAULT_CTOR();
)
