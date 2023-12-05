#include "BSML/Settings/UI/SettingsMenuListViewController.hpp"
#include "BSML/Settings/BSMLSettings.hpp"

#include "logging.hpp"
#include "assets.hpp"
#include "BSML.hpp"

DEFINE_TYPE(BSML, SettingsMenuListViewController);

namespace BSML {
    void SettingsMenuListViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        if (firstActivation) {
            DEBUG("DidActivate");
            parse_and_construct(Assets::Settings::List_bsml, transform, *this);

            auto r = rectTransform;
            r.sizeDelta = {35, 0};
            r.anchorMin = {0.5f, 0};
            r.anchorMax = {0.5f, 1};
        }

        DEBUG("Update Data: {}", fmt::ptr(list));
        if (list && list.m_CachedPtr) {
            list.data = BSMLSettings::get_instance().settingsMenus;
            if (list.tableView && list.tableView.m_CachedPtr) {
                list.tableView.ReloadData();
            }
        }
    }

    void SettingsMenuListViewController::SettingsClick(HMUI::TableView tableView, int idx) {
        INFO("Settings Click");
        SettingsMenu menu {list.data[idx].convert()};
        if (clickedMenu) clickedMenu(menu);
    }
}
