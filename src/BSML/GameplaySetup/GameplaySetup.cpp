#include "BSML/GameplaySetup/GameplaySetup.hpp"

#include "Helpers/getters.hpp"
#include "assets.hpp"
#include "logging.hpp"
#include "BSML.hpp"

#include "HMUI/ViewController_DidActivateDelegate.hpp"
#include "HMUI/ViewController_DidDeactivateDelegate.hpp"
#include "UnityEngine/Resources.hpp"
#include "GlobalNamespace/SinglePlayerLevelSelectionFlowCoordinator.hpp"
#include "GlobalNamespace/CampaignFlowCoordinator.hpp"
#include "GlobalNamespace/GameServerLobbyFlowCoordinator.hpp"


DEFINE_TYPE(BSML, GameplaySetup);

namespace BSML {
    SafePtr<GameplaySetup> GameplaySetup::instance;
    GameplaySetup GameplaySetup::get_instance() {
        if (!instance) {
            instance.emplace(GameplaySetup::New_ctor());
            instance.reuseIdentifier = "GameplaySetupCell";
        }
        return GameplaySetup(instance.ptr());
    }

    GameplaySetup::operator HMUI::TableView::IDataSource() {
        return HMUI::TableView::IDataSource(convert());
    }

    void GameplaySetup::Setup() {
        DEBUG("Setup");
        auto menus = this->menus;
        if (menus.size() == 0) return;
        gameplaySetupViewController = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::GameplaySetupViewController>().FirstOrDefault();
        auto vanillaItems = this->vanillaItems;
        vanillaItems->Clear();

        auto t = gameplaySetupViewController.transform;
        int childCount = t.childCount;
        for (int i = 0; i < childCount; i++) {
            auto child = t->GetChild(i);
            if (child.name != "HeaderPanel") {
                vanillaItems.Add(child);
            }
        }

        UnityEngine::RectTransform textSegmentedControl {t.Find("TextSegmentedControl").convert()};
        textSegmentedControl.sizeDelta = {0, 6};
        layoutGroup = textSegmentedControl.GetComponent<UnityEngine::UI::LayoutGroup>();

        parse_and_construct(Assets::GameplayMenu::GameplaySetup_bsml, t, *this);

        modsList.tableView.SetDataSource(*this, false);
        listParsed = false;

        auto didActivate = MakeDelegate<HMUI::ViewController::DidActivateDelegate>(
            std::function<void(bool, bool, bool)>(
            [self = *this](bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
            self.GameplaySetupDidActivate(firstActivation, addedToHierarchy, screenSystemEnabling);
        }));
        gameplaySetupViewController.add_didActivateEvent(didActivate);

        auto didDeactivate = MakeDelegate<HMUI::ViewController::DidDeactivateDelegate>(
            std::function<void(bool, bool)>(
            [self = *this](bool removedFromHierarchy, bool screenSystemDisabling) {
            self.GameplaySetupDidDeactivate(removedFromHierarchy, screenSystemDisabling);
        }));
        gameplaySetupViewController.add_didDeactivateEvent(didDeactivate);
        listModal.onHide = [self = *this]{ self.ClickedOffModal(); };
    }

    void GameplaySetup::GameplaySetupDidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        DEBUG("DidActivate");
        layoutGroup.m_RectChildren.Clear();

        MenuType menuType = MenuType::Custom;
        auto fc = Helpers::GetMainFlowCoordinator().YoungestChildFlowCoordinatorOrSelf();
        if (il2cpp_utils::try_cast<GlobalNamespace::CampaignFlowCoordinator>(fc).has_value()) {
            menuType = MenuType::Campaign;
        } else if (il2cpp_utils::try_cast<GlobalNamespace::SinglePlayerLevelSelectionFlowCoordinator>(fc).has_value()) {
            menuType = MenuType::Solo;
        } else if (il2cpp_utils::try_cast<GlobalNamespace::GameServerLobbyFlowCoordinator>(fc).has_value()) {
            menuType = MenuType::Online;
        }

        for (auto x : get_menus()) {
            auto menu = GameplaySetupMenu(x.convert());
            menu.SetVisible(menu.IsMenuType(menuType));
        }
    }

    void GameplaySetup::GameplaySetupDidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling) {
        DEBUG("DidDeactivate(removedFromHierarchy: {}, screenSystemDisabling: {})", removedFromHierarchy, screenSystemDisabling);

        if (!screenSystemDisabling) {
            tabSelector.textSegmentedControl.SelectCellWithNumber(0);
            vanillaTab.gameObject.SetActive(true);
            modsTab.gameObject.SetActive(false);
        }
    }

    void GameplaySetup::ClickedOffModal() {
        GameplaySetupDidActivate(false, false, false);
    }

    void GameplaySetup::ShowModal() {
        DEBUG("ShowModal");
        set_loaded(false);
        auto delegate = MakeSystemAction([self = *this]{
            DEBUG("Modal is shown");
            if (!self.listParsed) {
                DEBUG("Reloading data in list");
                self.modsList.tableView.ReloadData();
                self.listParsed = true;
            }
            DEBUG("Refreshing size");
            self.modsList.tableView.RefreshContentSize();
            self.loaded = true;
        });
        listModal.HMUI::ModalView::Show(true, true, delegate);
    }

    bool GameplaySetup::AddTab(std::string_view name, std::string_view content_key, bs_hook::Il2CppWrapperType host, MenuType menuType) {
        auto menus = this->menus;
        auto menu = std::find_if(menus.begin(), menus.end(), [name](auto x){ return GameplaySetupMenu(x.convert()).name == name; });
        if (menu != menus.end()) {
            return false;
        }

        menus.Add(GameplaySetupMenu::Make_new(name, content_key, host, menuType));
        return true;
    }

    bool GameplaySetup::AddTab(System::Type csType, std::string_view name, MenuType menuType) {
        auto menus = this->menus;
        auto menu = std::find_if(menus.begin(), menus.end(), [name](auto x){ return GameplaySetupMenu(x.convert()).name == name; });
        if (menu != menus.end()) {
            return false;
        }
        menus->Add(GameplaySetupMenu::Make_new(csType, name, menuType));
        return true;
    }

    bool GameplaySetup::AddTab(std::function<void(UnityEngine::GameObject, bool)> didActivate, std::string_view name, MenuType menuType) {
        auto menus = this->menus;
        auto menu = std::find_if(menus.begin(), menus.end(), [name](auto x){ return GameplaySetupMenu(x.convert()).name == name; });
        if (menu != menus.end()) {
            return false;
        }
        menus->Add(GameplaySetupMenu::Make_new(didActivate, name, menuType));
        return true;
    }

    void GameplaySetup::SetTabVisibility(std::string_view name, bool isVisible) {
        if (!gameplaySetupViewController || !gameplaySetupViewController.m_CachedPtr || !gameplaySetupViewController.isActiveAndEnabled) {
            return;
        }

        auto menus = this->menus;
        auto menu = std::find_if(menus.begin(), menus.end(), [name](auto x){ return GameplaySetupMenu(x.convert()).name == name; });
        if (menu != menus.end()) {
            GameplaySetupMenu((*menu).convert()).SetVisible(isVisible);
        }
    }

    bool GameplaySetup::RemoveTab(std::string_view name) {
        auto menus = this->menus;
        for (auto x : menus) {
            auto menu = GameplaySetupMenu(x.convert());
            if (menu->name == name) {
                menus.Remove(menu);
                return true;
            }
        }
        return false;
    }

    GameplaySetupCell* GameplaySetup::GetCell() {
        INFO("Getting Cell");
        auto cell = GameplaySetupCell(modsList.tableView.DequeueReusableCellForIdentifier(reuseIdentifier).convert());

        if (!cell || !cell.m_CachedPtr) {
            cell = UnityEngine::GameObject::New_ctor("GameplaySetupCell").AddComponent<GameplaySetupCell>();
            cell.interactable = true;
            cell.reuseIdentifier = reuseIdentifier;

            parse_and_construct(Assets::GameplayMenu::GameplaySetupCell_bsml, cell.transform, cell);
        }

        return cell;
    }

    float GameplaySetup::CellSize() {
        return 8.0f;
    }

    int GameplaySetup::NumberOfCells() {
        return get_menus().size();
    }

    HMUI::TableCell GameplaySetup::CellForIdx(HMUI::TableView tableView, int idx) {
        return GetCell().PopulateCell(GameplaySetupMenu(menus[idx].convert()));
    }


    ListWrapper<bs_hook::Il2CppWrapperType> GameplaySetup::get_menus() {
        if (!_menus) {
            _menus = List<bs_hook::Il2CppWrapperType>::New_ctor();
        }
        return _menus;
    }

    ListWrapper<UnityEngine::Transform*> GameplaySetup::get_vanillaItems() {
        if (!_vanillaItems) {
            _vanillaItems = List<UnityEngine::Transform>::New_ctor();
        }
        return _vanillaItems;
    }

    bool GameplaySetup::get_loaded() {
        return _loaded;
    }

    void GameplaySetup::set_loaded(bool value) {
        _loaded = value;
        if (modsList && modsList.m_CachedPtr) modsList.gameObject.SetActive(value);
        if (loading && loading.m_CachedPtr) loading.gameObject.SetActive(!value);
    }
}
