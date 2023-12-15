#include "hooking.hpp"

#include "HMUI/FlowCoordinator.hpp"
#include "HMUI/ViewController.hpp"

MAKE_AUTO_HOOK_MATCH(FlowCoordinator_ProvideInitialViewControllers, 
                &HMUI::FlowCoordinator::ProvideInitialViewControllers,
                void, 
                HMUI::FlowCoordinator* self, 
                HMUI::ViewController* mainViewController, 
                HMUI::ViewController* leftScreenViewController, 
                HMUI::ViewController* rightScreenViewController, 
                HMUI::ViewController* bottomScreenViewController, 
                HMUI::ViewController* topScreenViewController) {
    // if we are given a nullptr value, use the provided view controller instead, this should be fine I think
    leftScreenViewController = leftScreenViewController ? leftScreenViewController : self->_providedLeftScreenViewController;
    rightScreenViewController = rightScreenViewController ? rightScreenViewController : self->_providedRightScreenViewController;
    bottomScreenViewController = bottomScreenViewController ? bottomScreenViewController : self->_providedBottomScreenViewController;
    topScreenViewController = topScreenViewController ? topScreenViewController : self->_providedTopScreenViewController;
    mainViewController = mainViewController ? mainViewController : self->_providedMainViewController;

    FlowCoordinator_ProvideInitialViewControllers(self, mainViewController, leftScreenViewController, rightScreenViewController, bottomScreenViewController, topScreenViewController);
}
