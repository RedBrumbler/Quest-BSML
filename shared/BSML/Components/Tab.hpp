#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

namespace BSML {
    class TabSelector;
}

DECLARE_CLASS_CORDL(BSML, Tab, UnityEngine::MonoBehaviour,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(bs_hook::Il2CppWrapperType, selector);
        DECLARE_INSTANCE_FIELD(StringW, _tabName);
        DECLARE_INSTANCE_FIELD(StringW, _tabKey);
        DECLARE_INSTANCE_FIELD(bool, _isVisible);
    );

    FIELD_ACCESSOR(_tabName);
    FIELD_ACCESSOR(_tabKey);
    FIELD_ACCESSOR(_isVisible);
    /* Special property for forward declared field*/
    TabSelector __get_selector();
    void __set_selector(TabSelector selector);
    __declspec(property(get=__get_selector, put=__set_selector)) TabSelector selector;

    DECLARE_INSTANCE_METHOD(bool, get_isVisible);
    DECLARE_INSTANCE_METHOD(void, set_isVisible, bool value);
    __declspec(property(get=get_isVisible, put=set_isVisible)) bool isVisible;
    DECLARE_INSTANCE_METHOD(StringW, get_tabName);
    DECLARE_INSTANCE_METHOD(void, set_tabName, StringW value);
    __declspec(property(get=get_tabName, put=set_tabName)) StringW tabName;
    DECLARE_INSTANCE_METHOD(StringW, get_tabKey);
    DECLARE_INSTANCE_METHOD(void, set_tabKey, StringW value);
    __declspec(property(get=get_tabKey, put=set_tabKey)) StringW tabKey;
    DECLARE_CTOR(ctor);
)
