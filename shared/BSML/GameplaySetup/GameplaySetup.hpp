#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/UI/LayoutGroup.hpp"
#include "GlobalNamespace/GameplaySetupViewController.hpp"

#include "../Components/TabSelector.hpp"
#include "../Components/CustomListTableData.hpp"
#include "../Components/ModalView.hpp"
#include "HMUI/TableView_IDataSource.hpp"
#include "GameplaySetupCell.hpp"
#include "MenuType.hpp"

DECLARE_CLASS_CORDL_INTERFACES(BSML, GameplaySetup, bs_hook::Il2CppWrapperType, classof(HMUI::TableView::IDataSource*),
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(UnityEngine::UI::LayoutGroup, layoutGroup);
        DECLARE_INSTANCE_FIELD(GlobalNamespace::GameplaySetupViewController, gameplaySetupViewController);
        DECLARE_INSTANCE_FIELD(bool, listParsed);
        DECLARE_INSTANCE_FIELD(bool, _loaded);

        DECLARE_INSTANCE_FIELD(BSML::ModalView, listModal);
        DECLARE_INSTANCE_FIELD(CustomListTableData, modsList);
        DECLARE_INSTANCE_FIELD(ListWrapper<bs_hook::Il2CppWrapperType>, _menus);
        DECLARE_INSTANCE_FIELD(ListWrapper<UnityEngine::Transform>, _vanillaItems);

        DECLARE_INSTANCE_FIELD(HMUI::ImageView, loading);
        DECLARE_INSTANCE_FIELD(BSML::TabSelector, tabSelector);
        DECLARE_INSTANCE_FIELD(UnityEngine::Transform, vanillaTab);
        DECLARE_INSTANCE_FIELD(UnityEngine::Transform, modsTab);
        DECLARE_INSTANCE_FIELD(StringW, reuseIdentifier);
    );

    FIELD_ACCESSOR(layoutGroup);
    FIELD_ACCESSOR(gameplaySetupViewController);
    FIELD_ACCESSOR(listParsed);
    FIELD_ACCESSOR(_loaded);
    FIELD_ACCESSOR(listModal);
    FIELD_ACCESSOR(modsList);
    FIELD_ACCESSOR(_menus);
    FIELD_ACCESSOR(_vanillaItems);
    FIELD_ACCESSOR(loading);
    FIELD_ACCESSOR(tabSelector);
    FIELD_ACCESSOR(vanillaTab);
    FIELD_ACCESSOR(modsTab);
    FIELD_ACCESSOR(reuseIdentifier);

    DECLARE_INSTANCE_METHOD(ListWrapper<bs_hook::Il2CppWrapperType>, get_menus);
    __declspec(property(get=get_menus)) ListWrapper<bs_hook::Il2CppWrapperType> menus;

    DECLARE_INSTANCE_METHOD(ListWrapper<UnityEngine::Transform>, get_vanillaItems);
    __declspec(property(get=get_vanillaItems)) ListWrapper<UnityEngine::Transform> vanillaItems;

    DECLARE_INSTANCE_METHOD(bool, get_loaded);
    DECLARE_INSTANCE_METHOD(void, set_loaded, bool value);
    __declspec(property(get=get_loaded,put=set_loaded)) bool loaded;

    DECLARE_INSTANCE_METHOD(void, Setup);
    DECLARE_INSTANCE_METHOD(void, GameplaySetupDidActivate, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_INSTANCE_METHOD(void, GameplaySetupDidDeactivate, bool removedFromHierarchy, bool screenSystemDisabling);
    DECLARE_INSTANCE_METHOD(void, ClickedOffModal);
    DECLARE_INSTANCE_METHOD(void, ShowModal);

    DECLARE_INSTANCE_METHOD(GameplaySetupCell*, GetCell);
    DECLARE_OVERRIDE_METHOD(float, CellSize, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::TableView::IDataSource::CellSize>::get());
    DECLARE_OVERRIDE_METHOD(int, NumberOfCells, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::TableView::IDataSource::NumberOfCells>::get());
    DECLARE_OVERRIDE_METHOD(HMUI::TableCell, CellForIdx, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::TableView::IDataSource::CellForIdx>::get(), HMUI::TableView tableView, int idx);

    DECLARE_DEFAULT_CTOR();
    public:
        bool AddTab(std::string_view name, std::string_view content_key, bs_hook::Il2CppWrapperType host, MenuType menuType = MenuType::All);
        bool AddTab(System::Type csType, std::string_view name, MenuType menuType = MenuType::All);
        bool AddTab(std::function<void(UnityEngine::GameObject, bool)> didActivate, std::string_view name, MenuType menuType = MenuType::All);
        void SetTabVisibility(std::string_view name, bool isVisible);
        bool RemoveTab(std::string_view name);

        static GameplaySetup get_instance();

        operator HMUI::TableView::IDataSource();
    private:
        static SafePtr<GameplaySetup> instance;
)
