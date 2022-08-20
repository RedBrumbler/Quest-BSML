#include "hooking.hpp"
#include "logging.hpp"

#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "BSML/MenuButtons/MenuButtons.hpp"
#include "BSML/Settings/BSMLSettings.hpp"
#include "BSML/GameplaySetup/GameplaySetup.hpp"

MAKE_AUTO_HOOK_MATCH(MainFlowCoordinator_DidActivate, &GlobalNamespace::MainFlowCoordinator::DidActivate, void, GlobalNamespace::MainFlowCoordinator* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    INFO("MainFlowCoordinator_DidActivate");
    if (firstActivation) {
        BSML::MenuButtons::get_instance()->Setup();
        BSML::BSMLSettings::get_instance()->Setup();
        BSML::GameplaySetup::get_instance()->Setup();
    }

    MainFlowCoordinator_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
}
