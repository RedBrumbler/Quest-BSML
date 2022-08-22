#include "BSML/Settings/SettingsMenu.hpp"
#include "logging.hpp"

#include "Helpers/creation.hpp"
#include "BSML.hpp"
#include "BSMLDataCache_internal.hpp"
#include "assets.hpp"

#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Vector2.hpp"

DEFINE_TYPE(BSML, SettingsMenu);

namespace BSML {
    HMUI::ViewController* SettingsMenu::get_viewController() {
        if (!viewController || !viewController->m_CachedPtr.m_value) {
            Setup();
        }
        return viewController;
    }

    void SettingsMenu::Setup() {
        DEBUG("Setup");
        viewController = Helpers::CreateViewController<HMUI::ViewController*>();
        SetupViewControllerTransform(viewController);
        auto parser = parse_and_construct(get_content(), viewController->get_transform(), host);
        parserParams = parser->parserParams;
        didSetup = true;
    }

    std::string_view SettingsMenu::get_content() {
        auto entry = DataCache::Get(content_key);
        if (!entry) {
            return IncludedAssets::SettingsError_bsml;
        }

        auto data = entry->get_data();
        return std::string_view(reinterpret_cast<char*>(data.begin()), size_t(data.size()));
    }
    
    void SettingsMenu::SetupViewControllerTransform(HMUI::ViewController* viewController) {
        auto r = viewController->get_rectTransform();
        r->set_sizeDelta({110, 0});
        r->set_anchorMin({0.5f, 0});
        r->set_anchorMax({0.5f, 1});
    }

    SettingsMenu* SettingsMenu::Make_new(std::string_view name, std::string_view content, Il2CppObject* host, bool enableExtraButtons) {
        auto self = SettingsMenu::New_ctor();

        self->text = name;
        self->name = name;
        self->enableExtraButtons = enableExtraButtons;
        self->content_key = content;
        self->host = host;

        return self;
    }
}