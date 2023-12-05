#pragma once

#include "custom-types/shared/macros.hpp"
#include "HMUI/ModalView.hpp"

DECLARE_CLASS_CORDL(BSML, ModalView, HMUI::ModalView,

    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(bool, moveToCenter);
        DECLARE_INSTANCE_FIELD(bool, dismissOnBlockerClicked);
        public:
            std::function<void(void)> onHide;
    );

    FIELD_ACCESSOR(moveToCenter);
    FIELD_ACCESSOR(dismissOnBlockerClicked);
    FIELD_ACCESSOR(onHide);

    DECLARE_INSTANCE_METHOD(void, Awake);
    public:
    DECLARE_INSTANCE_METHOD(void, Show);
    DECLARE_INSTANCE_METHOD(void, Hide);
    DECLARE_INSTANCE_METHOD(void, BlockerClicked);

)
