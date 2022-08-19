#include "hooking.hpp"
#include "logging.hpp"

#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "BSML/MenuButtons/MenuButtons.hpp"

MAKE_AUTO_HOOK_MATCH(MainFlowCoordinator_DidActivate, &GlobalNamespace::MainFlowCoordinator::DidActivate, void, GlobalNamespace::MainFlowCoordinator* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    INFO("MainFlowCoordinator_DidActivate");
    if (firstActivation) {
        auto btns = BSML::MenuButtons::get_instance();
        btns->Setup();
    }

    MainFlowCoordinator_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
}