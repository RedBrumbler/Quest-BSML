#include "hooking.hpp"

#include "HMUI/ModalView.hpp"
#include "HMUI/Screen.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Canvas.hpp"
#include "UnityEngine/GameObject.hpp"

MAKE_AUTO_HOOK_MATCH(ModalView_Show, &HMUI::ModalView::Show, void, HMUI::ModalView* ptr, bool animated, bool moveToCenter, System::Action finishedCallback)
{
	HMUI::ModalView self{ptr};
	ModalView_Show(ptr, animated, moveToCenter, finishedCallback);
	auto cb = self._blockerGO.gameObject.GetComponent<UnityEngine::Canvas>();
	auto screen = self.transform.parent.gameObject.GetComponentInParent<HMUI::Screen>();
	auto canvases = screen.gameObject.GetComponentsInChildren<UnityEngine::Canvas>(true);

	int highest = 0;
	for (auto& canvas : canvases) {
		if (canvas.sortingLayerID == cb.sortingLayerID) {
			// if highest lower than current, assign
			if (highest < canvas.sortingOrder) {
				highest = canvas.sortingOrder;
			}
		}
	}

	highest ++;
	cb.set_overrideSorting(true);
	cb.set_sortingOrder(highest);

	auto cm = self.gameObject.GetComponent<UnityEngine::Canvas>();
	cm.overrideSorting = true;
	cm.sortingOrder = highest + 1;
}
