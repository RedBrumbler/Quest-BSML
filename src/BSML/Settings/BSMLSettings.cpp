#include "BSML/Settings/BSMLSettings.hpp"
#include "BSML/Settings/SettingsMenu.hpp"
#include "logging.hpp"

#include "Helpers/creation.hpp"
#include "Helpers/utilities.hpp"
#include "Helpers/getters.hpp"
#include "Helpers/delegates.hpp"

#include "assets.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/WaitForFixedUpdate.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/TextureWrapMode.hpp"
#include "UnityEngine/UI/Button_ButtonClickedEvent.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "Polyglot/LocalizedTextMeshProUGUI.hpp"

#include "GlobalNamespace/SharedCoroutineStarter.hpp"
#include "GlobalNamespace/OptionsViewController.hpp"
#include "HMUI/ButtonSpriteSwap.hpp"

DEFINE_TYPE(BSML, BSMLSettings);

namespace BSML {
    SafePtr<BSMLSettings> BSMLSettings::instance;
    BSMLSettings* BSMLSettings::get_instance() {
        if (!instance) {
            instance.emplace(BSMLSettings::New_ctor());
        }
        return instance.ptr();
    }

    ListWrapper<BSML::CustomCellInfo*> BSMLSettings::get_settingsMenus() {
        if (!settingsMenus) {
            settingsMenus = List<CustomCellInfo*>::New_ctor();
        }
        return settingsMenus;
    }
    ModSettingsFlowCoordinator* BSMLSettings::get_modSettingsFlowCoordinator() {
        if (!modSettingsFlowCoordinator || !modSettingsFlowCoordinator->m_CachedPtr.m_value) {
            modSettingsFlowCoordinator = Helpers::CreateFlowCoordinator<ModSettingsFlowCoordinator*>();
        }
        return modSettingsFlowCoordinator;
    }

    void BSMLSettings::Setup() {
        DEBUG("Setup");
        auto menus = get_settingsMenus();
        for (auto& cell : menus) {
            auto menu = reinterpret_cast<BSML::SettingsMenu*>(cell);
            if (menu->viewController && menu->viewController->m_CachedPtr.m_value) {
                UnityEngine::Object::DestroyImmediate(menu->viewController->get_gameObject());
            }
        }

        auto starter = GlobalNamespace::SharedCoroutineStarter::get_instance();
        if (addButtonCoroutine && addButtonCoroutine->m_Ptr.m_value) {
            starter->StopCoroutine(addButtonCoroutine);
        }

        if (!button || !button->m_CachedPtr.m_value) {
            addButtonCoroutine = starter->StartCoroutine(custom_types::Helpers::CoroutineHelper::New(AddButtonToMainScreen()));
        }

        isInitialized = true;
    }

    bool BSMLSettings::AddSettingsMenu(std::string_view name, std::string_view content_key, Il2CppObject* host, bool enableExtraButtons) {
        auto menus = get_settingsMenus();
        // if we find the same entry, early return
        if (std::find_if(menus.begin(), menus.end(), [&name](auto x){ return x->text == name;}) != menus.end()) {
            return false;
        }

        if (menus.size() == 0) {
            // add bsml about
            menus->Add(SettingsMenu::Make_new("BSML", MOD_ID "_settings_about", this, false));
        }

        auto menu = SettingsMenu::Make_new(name, content_key, host, enableExtraButtons);
        menus->Add(menu);
        if (isInitialized) {
            menu->Setup();
        }
        if (button && button->m_CachedPtr.m_value) {
            button->get_gameObject()->SetActive(true);
        }

        return true;
    }

    bool BSMLSettings::RemoveSettingsMenu(Il2CppObject* host) {
        auto menus = get_settingsMenus();
        for (auto& cell : menus) {
            auto menu = reinterpret_cast<BSML::SettingsMenu*>(cell);
            if (menu->host == host) {
                menus->Remove(menu);
                return true;
            }
        }
        return false;
    }

    void BSMLSettings::PresentSettings() {
        DEBUG("Presenting settings");
        auto modFC = get_modSettingsFlowCoordinator();
        modFC->isAnimating = true;

        auto fc = Helpers::GetMainFlowCoordinator()->YoungestChildFlowCoordinatorOrSelf();
        fc->PresentFlowCoordinator(modFC, MakeSystemAction([modFC]{
            modFC->ShowInitial();
            modFC->isAnimating = false;
        }), HMUI::ViewController::AnimationDirection::Horizontal, false, false);
    }

    custom_types::Helpers::Coroutine BSMLSettings::AddButtonToMainScreen() {
        addButtonCoroutine = nullptr;
        GlobalNamespace::OptionsViewController* optionsViewController = nullptr;
        auto wait = UnityEngine::WaitForFixedUpdate::New_ctor();
        while (!optionsViewController) {
            optionsViewController = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::OptionsViewController*>().FirstOrDefault();
            co_yield reinterpret_cast<System::Collections::IEnumerator*>(wait);
        }

        button = UnityEngine::Object::Instantiate(optionsViewController->settingsButton, optionsViewController->get_transform()->Find("Wrapper"));
        button->GetComponentInChildren<Polyglot::LocalizedTextMeshProUGUI*>()->set_Key("Mod Settings");
        auto onClick = UnityEngine::UI::Button::ButtonClickedEvent::New_ctor();
        button->set_onClick(onClick);
        onClick->AddListener(MakeUnityAction(this, ___PresentSettings_MethodRegistrator.get()));

        if (get_settingsMenus().size() == 0)
            button->get_gameObject()->SetActive(false);
        
        normal = Utilities::LoadSpriteRaw(IncludedAssets::mods_idle_png);
        normal->get_texture()->set_wrapMode(UnityEngine::TextureWrapMode::Clamp);
        hover = Utilities::LoadSpriteRaw(IncludedAssets::mods_selected_png);
        hover->get_texture()->set_wrapMode(UnityEngine::TextureWrapMode::Clamp);

        auto buttonSpriteSwap = button->GetComponent<HMUI::ButtonSpriteSwap*>();
        buttonSpriteSwap->disabledStateSprite = normal;
        buttonSpriteSwap->normalStateSprite = normal;
        buttonSpriteSwap->highlightStateSprite = hover;
        buttonSpriteSwap->pressedStateSprite = hover;
        button->get_transform()->SetAsFirstSibling();
        co_return;
    }
}
