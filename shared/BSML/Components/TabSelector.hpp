#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "HMUI/TextSegmentedControl.hpp"
#include "HMUI/SegmentedControl.hpp"
#include "Tab.hpp"
#include "../Parsing/BSMLParserParams.hpp"

DECLARE_CLASS_CORDL(BSML, TabSelector, UnityEngine::MonoBehaviour,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(HMUI::TextSegmentedControl, textSegmentedControl);
        DECLARE_INSTANCE_FIELD(StringW, tabTag);
        DECLARE_INSTANCE_FIELD(StringW, leftButtonTag);
        DECLARE_INSTANCE_FIELD(StringW, rightButtonTag);
        DECLARE_INSTANCE_FIELD(ListWrapper<Tab>, tabs);
        DECLARE_INSTANCE_FIELD(ListWrapper<Tab>, visibleTabs);
        DECLARE_INSTANCE_FIELD(int, _pageCount);
        DECLARE_INSTANCE_FIELD(int, currentPage);
        DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button, leftButton);
        DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button, rightButton);
        DECLARE_INSTANCE_FIELD(int, lastClickedPage);
        DECLARE_INSTANCE_FIELD(int, lastClickedIndex);
        DECLARE_INSTANCE_FIELD(bool, shouldRefresh);
    );

    FIELD_ACCESSOR(textSegmentedControl);
    FIELD_ACCESSOR(tabTag);
    FIELD_ACCESSOR(leftButtonTag);
    FIELD_ACCESSOR(rightButtonTag);
    FIELD_ACCESSOR(tabs);
    FIELD_ACCESSOR(visibleTabs);
    FIELD_ACCESSOR(_pageCount);
    FIELD_ACCESSOR(currentPage);
    FIELD_ACCESSOR(leftButton);
    FIELD_ACCESSOR(rightButton);
    FIELD_ACCESSOR(lastClickedPage);
    FIELD_ACCESSOR(lastClickedIndex);
    FIELD_ACCESSOR(shouldRefresh);

    DECLARE_INSTANCE_METHOD(int, get_page);
    __declspec(property(get=get_page)) int page;
    DECLARE_INSTANCE_METHOD(int, get_pageCount);
    DECLARE_INSTANCE_METHOD(void, set_pageCount, int value);
    __declspec(property(get=get_pageCount, put=set_pageCount)) int pageCount;

    DECLARE_INSTANCE_METHOD(void, TabSelected, HMUI::SegmentedControl* segmentedControl, int index);
    DECLARE_INSTANCE_METHOD(void, Refresh);
    DECLARE_INSTANCE_METHOD(void, SetSegmentedControlTexts, ListWrapper<Tab*> tabs);
    DECLARE_INSTANCE_METHOD(void, PageLeft);
    DECLARE_INSTANCE_METHOD(void, PageRight);
    DECLARE_INSTANCE_METHOD(void, OnEnable);

    DECLARE_CTOR(ctor);

    public:
        void Setup(const BSMLParserParams& parserParams);
)
