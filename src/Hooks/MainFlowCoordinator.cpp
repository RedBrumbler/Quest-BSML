#include "hooking.hpp"
#include "logging.hpp"

#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "GlobalNamespace/PlayerOptionsViewController.hpp"
#include "BSML/MenuButtons/MenuButtons.hpp"
#include "BSML/Settings/BSMLSettings.hpp"
#include "BSML/GameplaySetup/GameplaySetup.hpp"

#include "HMUI/ViewController_AnimationType.hpp"
#include "Polyglot/Localization.hpp"

MAKE_AUTO_HOOK_MATCH(MainFlowCoordinator_DidActivate, &GlobalNamespace::MainFlowCoordinator::DidActivate, void, GlobalNamespace::MainFlowCoordinator* ptr, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    INFO("MainFlowCoordinator_DidActivate");
    if (firstActivation) {
        BSML::MenuButtons::get_instance()->Setup();
        BSML::BSMLSettings::get_instance()->Setup();
        BSML::GameplaySetup::get_instance()->Setup();
    }

    MainFlowCoordinator_DidActivate(ptr, firstActivation, addedToHierarchy, screenSystemEnabling);
}

MAKE_AUTO_HOOK_ORIG_MATCH(MainFlowCoordinator_TopViewControllerWillChange, &GlobalNamespace::MainFlowCoordinator::TopViewControllerWillChange, void, GlobalNamespace::MainFlowCoordinator* ptr, HMUI::ViewController oldViewController, HMUI::ViewController newViewController, HMUI::ViewController::AnimationType animationType)
{
	GlobalNamespace::MainFlowCoordinator self{ptr};
    // doesnt call orig!
    if (newViewController.Equals(self.mainMenuViewController))
	{
		self.SetLeftScreenViewController(self.providedLeftScreenViewController, animationType);
		self.SetRightScreenViewController(self.providedRightScreenViewController, animationType);
		self.SetBottomScreenViewController(nullptr, animationType);
	}
	else
	{
		self.SetLeftScreenViewController(nullptr, animationType);
		self.SetRightScreenViewController(nullptr, animationType);
		self.SetBottomScreenViewController(nullptr, animationType);
	}

    /*
	if (newViewController.Equals(self.howToPlayViewController))
	{
        static ConstString LABEL_HOW_TO_PLAY("LABEL_HOW_TO_PLAY");
        self.SetTitle(Polyglot::Localization::Get(LABEL_HOW_TO_PLAY), animationType);
		self.SetBottomScreenViewController(self.playerStatisticsViewController, animationType);
        self.showBackButton = true;
		return;
	}
    */

	if (newViewController.Equals(self.playerOptionsViewController))
	{
        static ConstString BUTTON_PLAYER_OPTIONS("BUTTON_PLAYER_OPTIONS");
        self.SetTitle(Polyglot::Localization::Get(BUTTON_PLAYER_OPTIONS), animationType);
        self.showBackButton = true;
		return;
	}
	if (newViewController.Equals(self.optionsViewController))
	{
        static ConstString LABEL_OPTIONS("LABEL_OPTIONS");
        self.SetTitle(Polyglot::Localization::Get(LABEL_OPTIONS), animationType);
        self.showBackButton = true;
		return;
	}
	self.SetTitle("", animationType);
    self.showBackButton = false;
}
