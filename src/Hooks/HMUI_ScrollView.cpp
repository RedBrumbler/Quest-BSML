#include "hooking.hpp"
#include "logging.hpp"

#include "BSML/Components/ScrollableContainer.hpp"
#include "HMUI/ScrollView.hpp"

bool compareKlass(Il2CppClass* other) {
    static Il2CppClass* klass = BSML::ScrollableContainer::___TypeRegistration::get()->klass();
    return other == klass;
}

#define VOID_OVERRIDE(method)                                                               \
MAKE_AUTO_HOOK_MATCH(ScrollView_##method, &ScrollView::method, void, ScrollView* self) {    \
    INFO("Method " #method " called");                                                      \
    if (compareKlass(self->klass)) {                                                        \
        INFO("Method " #method " overridden");                                              \
        reinterpret_cast<BSML::ScrollableContainer*>(self)->method();                       \
        return;                                                                             \
    }                                                                                       \
    ScrollView_##method(self);                                                              \
}

using namespace HMUI;

MAKE_AUTO_HOOK_MATCH(ScrollView_ScrollTo, &ScrollView::ScrollTo, void, ScrollView* self, float dstPosY, bool animated) {
    INFO("Method ScrollTo called");
    if (compareKlass(self->klass)) {
        INFO("Method ScrollTo overridden");
        reinterpret_cast<BSML::ScrollableContainer*>(self)->ScrollTo(dstPosY, animated);
        return;
    }
    ScrollView_ScrollTo(self, dstPosY, animated);
}

MAKE_AUTO_HOOK_MATCH(ScrollView_ScrollToWorldPositionIfOutsideArea, &ScrollView::ScrollToWorldPositionIfOutsideArea, void, ScrollView* self, UnityEngine::Vector3 worldPosition, float pageRelativePosition, float relativeBoundaryStart, float relativeBoundaryEnd, bool animated) {
    INFO("Method ScrollToWorldPositionIfOutsideArea called");
    if (compareKlass(self->klass)) {
        INFO("Method ScrollTo overridden");
        reinterpret_cast<BSML::ScrollableContainer*>(self)->ScrollToWorldPositionIfOutsideArea(worldPosition, pageRelativePosition, relativeBoundaryStart, relativeBoundaryEnd, animated);
        return;
    }
    ScrollView_ScrollToWorldPositionIfOutsideArea(self, worldPosition, pageRelativePosition, relativeBoundaryStart, relativeBoundaryEnd, animated);
}

MAKE_AUTO_HOOK_MATCH(ScrollView_ScrollToWorldPosition, &ScrollView::ScrollToWorldPosition, void, ScrollView* self, UnityEngine::Vector3 worldPosition, float pageRelativePosition, bool animated) {
    INFO("Method ScrollToWorldPosition called");
    if (compareKlass(self->klass)) {
        INFO("Method ScrollToWorldPosition overridden");
        reinterpret_cast<BSML::ScrollableContainer*>(self)->ScrollToWorldPosition(worldPosition, pageRelativePosition, animated);
        return;
    }
    ScrollView_ScrollToWorldPosition(self, worldPosition, pageRelativePosition, animated);
}

MAKE_AUTO_HOOK_MATCH(ScrollView_UpdateVerticalScrollIndicator, &ScrollView::UpdateVerticalScrollIndicator, void, ScrollView* self, float posY) {
    INFO("Method UpdateVerticalScrollIndicator called");
    if (compareKlass(self->klass)) {
        INFO("Method UpdateVerticalScrollIndicator overridden");
        reinterpret_cast<BSML::ScrollableContainer*>(self)->UpdateVerticalScrollIndicator(posY);
        return;
    }
    ScrollView_UpdateVerticalScrollIndicator(self, posY);
}

MAKE_AUTO_HOOK_MATCH(ScrollView_SetDestinationPos, &ScrollView::SetDestinationPos, void, ScrollView* self, float posY) {
    INFO("Method SetDestinationPos called");
    if (compareKlass(self->klass)) {
        INFO("Method SetDestinationPos overridden");
        reinterpret_cast<BSML::ScrollableContainer*>(self)->SetDestinationPosY(posY);
        return;
    }
    ScrollView_SetDestinationPos(self, posY);
}

VOID_OVERRIDE(Awake);
VOID_OVERRIDE(Update);
VOID_OVERRIDE(RefreshButtons);
VOID_OVERRIDE(PageUpButtonPressed);
VOID_OVERRIDE(PageDownButtonPressed);