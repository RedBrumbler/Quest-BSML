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

DECLARE_CLASS_CODEGEN_INTERFACES(BSML, GameplaySetup, Il2CppObject, classof(HMUI::TableView::IDataSource*),
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::LayoutGroup*, layoutGroup);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::GameplaySetupViewController*, gameplaySetupViewController);
    DECLARE_INSTANCE_FIELD(bool, listParsed);
    DECLARE_INSTANCE_FIELD(bool, _loaded);
    
    DECLARE_INSTANCE_FIELD(BSML::ModalView*, listModal);
    DECLARE_INSTANCE_FIELD(CustomListTableData*, modsList);
    DECLARE_INSTANCE_FIELD(List<Il2CppObject*>*, _menus);
    DECLARE_INSTANCE_FIELD(List<UnityEngine::Transform*>*, _vanillaItems);

    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, loading);
    DECLARE_INSTANCE_FIELD(BSML::TabSelector*, tabSelector);
    DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, vanillaTab);
    DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, modsTab);
    DECLARE_INSTANCE_FIELD(StringW, reuseIdentifier);

    DECLARE_INSTANCE_METHOD(ListWrapper<Il2CppObject*>, get_menus);
    DECLARE_INSTANCE_METHOD(ListWrapper<UnityEngine::Transform*>, get_vanillaItems);
    DECLARE_INSTANCE_METHOD(bool, get_loaded);
    DECLARE_INSTANCE_METHOD(void, set_loaded, bool value);

    DECLARE_INSTANCE_METHOD(void, Setup);
    DECLARE_INSTANCE_METHOD(void, GameplaySetupDidActivate, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_INSTANCE_METHOD(void, GameplaySetupDidDeactivate, bool removedFromHierarchy, bool screenSystemDisabling);
    DECLARE_INSTANCE_METHOD(void, ClickedOffModal);
    DECLARE_INSTANCE_METHOD(void, ShowModal);

    DECLARE_INSTANCE_METHOD(GameplaySetupCell*, GetCell);
    DECLARE_OVERRIDE_METHOD(float, CellSize, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::TableView::IDataSource::CellSize>::get());
    DECLARE_OVERRIDE_METHOD(int, NumberOfCells, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::TableView::IDataSource::NumberOfCells>::get());
    DECLARE_OVERRIDE_METHOD(HMUI::TableCell*, CellForIdx, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::TableView::IDataSource::CellForIdx>::get(), HMUI::TableView* tableView, int idx);

    DECLARE_DEFAULT_CTOR();
    public:
        bool AddTab(std::string_view name, std::string_view content_key, Il2CppObject* host, MenuType menuType = MenuType::All);
        void SetTabVisibility(std::string_view name, bool isVisible);
        bool RemoveTab(std::string_view name);

        static GameplaySetup* get_instance();

        HMUI::TableView::IDataSource* i_DataSource();
    private:
        static SafePtr<GameplaySetup> instance;
)