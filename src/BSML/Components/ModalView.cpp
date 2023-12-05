#include "BSML/Components/ModalView.hpp"
#include "Helpers/delegates.hpp"

DEFINE_TYPE(BSML, ModalView);

namespace BSML {
    void ModalView::Awake() {
        add_blockerClickedEvent(MakeSystemAction(convert(), ___BlockerClicked_MethodRegistrator.info));
    }

    void ModalView::Show() {

        this->::HMUI::ModalView::Show(true, moveToCenter, System::Action(nullptr));
    }

    void ModalView::Hide() {
        this->::HMUI::ModalView::Hide(true, System::Action(nullptr));
    }

    void ModalView::BlockerClicked() {
        if (onHide) {
            onHide();
        }

        if (dismissOnBlockerClicked) {
            Hide();
        }
    }
}
