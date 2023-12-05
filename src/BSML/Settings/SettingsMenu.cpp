#include "logging.hpp"
#include "BSML/Settings/SettingsMenu.hpp"

#include "Helpers/creation.hpp"
#include "BSML.hpp"
#include "BSMLDataCache_internal.hpp"
#include "assets.hpp"

#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "HMUI/ViewController_DidActivateDelegate.hpp"
#include "custom-types/shared/delegate.hpp"

DEFINE_TYPE(BSML, SettingsMenu);

namespace BSML {
    bool SettingsMenu::get_didSetup() {
        return _viewController && _viewController.m_CachedPtr || flowCoordinator && flowCoordinator.m_CachedPtr;
    }

    HMUI::ViewController SettingsMenu::get_viewController() {
        if (!get_didSetup()) {
            Setup();
        }
        return _viewController;
    }

    void SettingsMenu::Setup() {
        DEBUG("Setup");
        switch (menuSource) {
            case MenuSource::BSMLContent:
                _viewController = Helpers::CreateViewController<HMUI::ViewController>();
                SetupViewControllerTransform(_viewController);
                parserParams = parse_and_construct(get_content(), _viewController.transform, host)->parserParams;
                break;
            case MenuSource::FlowCoordinator:
                flowCoordinator = Helpers::CreateFlowCoordinator(csType);
                break;
            case MenuSource::ViewController:
                _viewController = Helpers::CreateViewController(csType);
                SetupViewControllerTransform(_viewController);
                break;
            case MenuSource::Method:
                _viewController = Helpers::CreateViewController<HMUI::ViewController>();
                SetupViewControllerTransform(_viewController);
                _viewController.add_didActivateEvent(custom_types::MakeDelegate<HMUI::ViewController::DidActivateDelegate>(_viewController, viewControllerDidActivate));
                break;
            case MenuSource::Component:
                throw std::runtime_error("Invalid menusource passed to settings menu!");
        }
    }

    std::string_view SettingsMenu::get_content() {
        auto entry = DataCache::Get(content_key);
        if (!entry) {
            return Assets::Settings::Error_bsml;
        }

        auto data = entry->get_data();
        return std::string_view(reinterpret_cast<char*>(data.begin()), size_t(data.size()));
    }

    void SettingsMenu::SetupViewControllerTransform(HMUI::ViewController _viewController) {
        auto r = _viewController.rectTransform;
        r.sizeDelta = {110, 0};
        r.anchorMin = {0.5f, 0};
        r.anchorMax = {0.5f, 1};
    }

    SettingsMenu SettingsMenu::Make_new(std::string_view name, std::string_view content, bs_hook::Il2CppWrapperType host, bool enableExtraButtons) {
        auto self = SettingsMenu::New_ctor();

        self.text = name;
        self.name = name;
        self.enableExtraButtons = enableExtraButtons;
        self.content_key = content;
        self.host = host;
        self.menuSource = MenuSource::BSMLContent;

        return self;
    }

    SettingsMenu SettingsMenu::Make_new(std::string_view name, System::Type csType, MenuSource menuSource, bool enableExtraButtons) {
        auto self = SettingsMenu::New_ctor();

        self.text = name;
        self.name = name;
        self.enableExtraButtons = enableExtraButtons;
        self.csType = csType;
        self.menuSource = menuSource;

        return self;
    }

    SettingsMenu SettingsMenu::Make_new(std::string_view name, std::function<void(HMUI::ViewController, bool, bool, bool)> viewControllerDidActivate, bool enableExtraButtons) {
        auto self = SettingsMenu::New_ctor();

        self.text = name;
        self.name = name;
        self.enableExtraButtons = enableExtraButtons;
        self.viewControllerDidActivate = viewControllerDidActivate;
        self.menuSource = MenuSource::Method;

        return self;
    }

}
