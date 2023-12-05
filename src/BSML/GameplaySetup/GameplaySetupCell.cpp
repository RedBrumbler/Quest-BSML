#include "BSML/GameplaySetup/GameplaySetupCell.hpp"
#include "logging.hpp"

#include "BSML/Components/ExternalComponents.hpp"

DEFINE_TYPE(BSML, GameplaySetupCell);

namespace BSML {
    GameplaySetupCell GameplaySetupCell::PopulateCell(GameplaySetupMenu menu) {
        DEBUG("Populating GameplaySetupCell");
        tab = menu;

        toggle.text = name;
        toggle.ReceiveValue();

        return *this;
    }

    StringW GameplaySetupCell::get_name() {
        return tab ? tab.name : "";
    }
    bool GameplaySetupCell::get_visible() {
        return tab && tab.visible;
    }

    void GameplaySetupCell::set_visible(bool value) {
        if (tab) {
            tab.visible = value;
            toggle.ReceiveValue();
        }
    }
}
