#pragma once

#include "custom-types/shared/macros.hpp"
#include "../Components/Tab.hpp"
#include "MenuType.hpp"
#include "../MenuSource.hpp"
#include <string>

DECLARE_CLASS_CORDL(BSML, GameplaySetupMenu, bs_hook::Il2CppWrapperType,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(StringW, name);
        DECLARE_INSTANCE_FIELD(StringW, content_key);
        DECLARE_INSTANCE_FIELD(bs_hook::Il2CppWrapperType, host);
        DECLARE_INSTANCE_FIELD(MenuType, menuType);
        DECLARE_INSTANCE_FIELD(Tab, tab);
        DECLARE_INSTANCE_FIELD(MenuSource, menuSource);
        DECLARE_INSTANCE_FIELD(System::Type, csType);
        std::function<void(UnityEngine::GameObject, bool)> didActivate;
    );

    FIELD_ACCESSOR(name);
    FIELD_ACCESSOR(content_key);
    FIELD_ACCESSOR(host);
    FIELD_ACCESSOR(menuType);
    FIELD_ACCESSOR(tab);
    FIELD_ACCESSOR(menuSource);
    FIELD_ACCESSOR(csType);
    FIELD_ACCESSOR(didActivate);

    DECLARE_INSTANCE_METHOD(bool, get_visible);
    DECLARE_INSTANCE_METHOD(void, set_visible, bool value);
    __declspec(property(get=get_visible,put=set_visible)) bool visible;

    DECLARE_INSTANCE_METHOD(void, Setup);
    DECLARE_INSTANCE_METHOD(void, PostParse);
    DECLARE_INSTANCE_METHOD(void, SetVisible, bool isVisible);

    public:
        static GameplaySetupMenu* Make_new(std::string_view name, std::string_view content_key, bs_hook::Il2CppWrapperType host, BSML::MenuType menuType = BSML::MenuType::All);
        static GameplaySetupMenu* Make_new(System::Type csType, std::string_view name, BSML::MenuType menuType = BSML::MenuType::All);
        static GameplaySetupMenu* Make_new(std::function<void(UnityEngine::GameObject, bool)> didActivate, std::string_view name, BSML::MenuType menuType = BSML::MenuType::All);

        bool get_content(std::string_view& content);
        bool IsMenuType(BSML::MenuType toCheck);

        DECLARE_DEFAULT_CTOR();
)
