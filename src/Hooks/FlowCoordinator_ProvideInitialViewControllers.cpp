#include "hooking.hpp"

#include "HMUI/FlowCoordinator.hpp"
#include "HMUI/ViewController.hpp"

MAKE_AUTO_HOOK_MATCH(FlowCoordinator_ProvideInitialViewControllers,
                &HMUI::FlowCoordinator::ProvideInitialViewControllers,
                void,
                HMUI::FlowCoordinator* ptr,
                HMUI::ViewController mainViewController,
                HMUI::ViewController leftScreenViewController,
                HMUI::ViewController rightScreenViewController,
                HMUI::ViewController bottomScreenViewController,
                HMUI::ViewController topScreenViewController) {
    HMUI::FlowCoordinator self{ptr};
    // if we are given a nullptr value, use the provided view controller instead, this should be fine I think
    leftScreenViewController = (leftScreenViewController.convert() && leftScreenViewController.m_CachedPtr) ? leftScreenViewController : self.providedLeftScreenViewController;
    rightScreenViewController = (rightScreenViewController.convert() && rightScreenViewController.m_CachedPtr) ? rightScreenViewController : self.providedRightScreenViewController;
    bottomScreenViewController = (bottomScreenViewController.convert() && bottomScreenViewController.m_CachedPtr) ? bottomScreenViewController : self.providedBottomScreenViewController;
    topScreenViewController = (topScreenViewController.convert() && topScreenViewController.m_CachedPtr) ? topScreenViewController : self.providedTopScreenViewController;
    mainViewController = (mainViewController.convert() && mainViewController.m_CachedPtr) ? mainViewController : self.providedMainViewController;

    FlowCoordinator_ProvideInitialViewControllers(ptr, mainViewController, leftScreenViewController, rightScreenViewController, bottomScreenViewController, topScreenViewController);
}
