#pragma once

#include "custom-types/shared/macros.hpp"
#include "HMUI/ScrollView.hpp"
#include "UnityEngine/Vector3.hpp"
#include "System/Action.hpp"

DECLARE_CLASS_CORDL(BSML, ScrollableContainer, HMUI::ScrollView,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(bool, _alignBottom);
        DECLARE_INSTANCE_FIELD(bool, _maskOverflow);
        DECLARE_INSTANCE_FIELD(float, contentHeight);
        DECLARE_INSTANCE_FIELD(bool, runScrollAnim);
        DECLARE_INSTANCE_FIELD(bool, scrollToBottomOnUpdate);
        DECLARE_INSTANCE_FIELD(System::Action, upButtonAction);
        DECLARE_INSTANCE_FIELD(System::Action, downButtonAction);
    );

    FIELD_ACCESSOR(_alignBottom);
    FIELD_ACCESSOR(_maskOverflow);
    FIELD_ACCESSOR(contentHeight);
    FIELD_ACCESSOR(runScrollAnim);
    FIELD_ACCESSOR(scrollToBottomOnUpdate);
    FIELD_ACCESSOR(upButtonAction);
    FIELD_ACCESSOR(downButtonAction);

    DECLARE_INSTANCE_METHOD(bool, get_alignBottom);
    DECLARE_INSTANCE_METHOD(void, set_alignBottom, bool value);
    __declspec(property(get=get_alignBottom,put=set_alignBottom)) bool alignBottom;

    DECLARE_INSTANCE_METHOD(bool, get_maskOverflow);
    DECLARE_INSTANCE_METHOD(void, set_maskOverflow, bool value);
    __declspec(property(get=get_maskOverflow,put=set_maskOverflow)) bool maskOverflow;

    DECLARE_INSTANCE_METHOD(float, get_scrollPageHeight);
    __declspec(property(get=get_scrollPageHeight)) float scrollPageHeight ;

    DECLARE_INSTANCE_METHOD(void, UpdateViewPortMask);
    DECLARE_INSTANCE_METHOD(void, Awake);
    DECLARE_INSTANCE_METHOD(void, RefreshBindings);
    DECLARE_INSTANCE_METHOD(void, RefreshContent);
    DECLARE_INSTANCE_METHOD(void, RefreshButtons);
    DECLARE_INSTANCE_METHOD(void, ContentSizeUpdated);
    DECLARE_INSTANCE_METHOD(void, Update);
    DECLARE_INSTANCE_METHOD(void, ComputeScrollFocusPosY);
    DECLARE_INSTANCE_METHOD(void, UpdateVerticalScrollIndicator, float posY);
    DECLARE_INSTANCE_METHOD(void, ScrollDown, bool animated);
    DECLARE_INSTANCE_METHOD(void, ScrollToWorldPosition, UnityEngine::Vector3 worldPosition, float pageRelativePosition, bool animated);
    DECLARE_INSTANCE_METHOD(void, ScrollToWorldPositionIfOutsideArea, UnityEngine::Vector3 worldPosition, float pageRelativePosition, float relativeBoundaryStart, float relativeBoundaryEnd, bool animated);
    DECLARE_INSTANCE_METHOD(void, ScrollTo, float dstPosY, bool animated);
    DECLARE_INSTANCE_METHOD(void, ScrollToNormalized, float dstPosY, bool animated);
    DECLARE_INSTANCE_METHOD(void, PageUpButtonPressed);
    DECLARE_INSTANCE_METHOD(void, PageDownButtonPressed);
    DECLARE_INSTANCE_METHOD(void, SetDestinationPosY, float value);

    public:
        float get_maxPosition();
        __declspec(property(get=get_maxPosition)) float maxPosition ;
)
