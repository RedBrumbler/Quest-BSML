#include "BSML/Settings/UI/ModSettingsFlowCoordinator.hpp"
#include "BSML/Settings/BSMLSettings.hpp"
#include "logging.hpp"

#include "assets.hpp"
#include "BSML.hpp"
#include "Helpers/creation.hpp"
#include "Helpers/getters.hpp"

#include "GlobalNamespace/MenuTransitionsHelper.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"

DEFINE_TYPE(BSML, ModSettingsFlowCoordinator);

namespace BSML {
    void ModSettingsFlowCoordinator::ctor() {
        static auto baseKlass = classof(HMUI::FlowCoordinator*);
        custom_types::InvokeBaseCtor(baseKlass, this);
        submenuStack = Stack<HMUI::ViewController*>::New_ctor();
    }

    void ModSettingsFlowCoordinator::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        if (!firstActivation) return;
        DEBUG("DidActivate");
        SetTitle("Mod Settings", HMUI::ViewController::AnimationType::In);
        navigationController = Helpers::CreateViewController<HMUI::NavigationController*>();
        auto parser = parse_and_construct(IncludedAssets::SettingsButtons_bsml, navigationController->get_transform(), this);
        parserParams = parser->parserParams;

        settingsMenuListViewController = Helpers::CreateViewController<SettingsMenuListViewController*>();
        settingsMenuListViewController->clickedMenu = [this](auto menu) { this->OpenMenu(menu); };
        DEBUG("SetViewControllerToNavigationController: {}, {}", fmt::ptr(navigationController), fmt::ptr(settingsMenuListViewController));
        SetViewControllerToNavigationController(navigationController, settingsMenuListViewController);
        DEBUG("ProvideInitialViewControllers");
        ProvideInitialViewControllers(navigationController, nullptr, nullptr, nullptr, nullptr);
        DEBUG("Done");
    }

    void ModSettingsFlowCoordinator::ShowInitial() {
        DEBUG("Showing Initial");
        if (activeController && activeController->m_CachedPtr.m_value) {
            return;
        }

        settingsMenuListViewController->list->tableView->SelectCellWithIdx(0, false);
        auto menus = BSMLSettings::get_instance()->get_settingsMenus();
        if (menus.size() > 0) {
            OpenMenu(reinterpret_cast<SettingsMenu*>(menus[0]));
        }
        isPresenting = true;
    }

    void ModSettingsFlowCoordinator::OpenMenu(SettingsMenu* menu) {
        if (!menu->didSetup) {
            menu->Setup();
            menu->parserParams->AddEvent("back", std::bind(&ModSettingsFlowCoordinator::Back, this));
        }

        if (bottomButtons && bottomButtons->m_CachedPtr.m_value) {
            bottomButtons->get_gameObject()->SetActive(menu->showExtraButtons);
        }
        OpenMenu(menu->get_viewController(), false, false);
    }

    void ModSettingsFlowCoordinator::OpenMenu(HMUI::ViewController* viewController, bool isSubmenu, bool isBack) {
        if (isPresenting) return;
        if (!isBack)
        {
            if (isSubmenu)
                submenuStack->Push(activeController);
            else
                submenuStack->Clear();
        }

        bool wasActive = activeController && activeController->m_CachedPtr.m_value;
        if (wasActive)
            PopViewControllerFromNavigationController(navigationController, nullptr, true);
        auto delegate = MakeSystemAction([this]{
            this->isPresenting = false;
            if (this->bottomButtons && this->bottomButtons->m_CachedPtr.m_value) {
                this->bottomButtons->SetAsLastSibling();
            }
        });
        PushViewControllerToNavigationController(navigationController, viewController, delegate, wasActive);
        activeController = viewController;
    }

    void ModSettingsFlowCoordinator::Ok() {
        EmitEventToAll("apply");
        // make ur mods not crash on soft restart lul
        UnityEngine::Object::FindObjectOfType<GlobalNamespace::MenuTransitionsHelper*>()->RestartGame(nullptr);
    }

    void ModSettingsFlowCoordinator::Cancel() {
        if (isPresenting || isAnimating) return;
        parentFlowCoordinator->DismissFlowCoordinator(this, HMUI::ViewController::AnimationDirection::Vertical, nullptr, false);
        EmitEventToAll("cancel");
    }

    void ModSettingsFlowCoordinator::Back() {
        if (submenuStack->get_Count() > 0) {
            OpenMenu(submenuStack->Pop(), false, true);
        }
    }

    void ModSettingsFlowCoordinator::EmitEventToAll(std::string_view ev) {
        auto menus = BSMLSettings::get_instance()->get_settingsMenus();
        for (auto cell : menus) {
            auto menu = reinterpret_cast<SettingsMenu*>(cell);
            if (menu->didSetup) {
                menu->parserParams->EmitEvent(std::string(ev));
            }
        }

    }
}