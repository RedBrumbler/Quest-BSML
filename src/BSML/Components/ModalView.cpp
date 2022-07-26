#include "BSML/Components/ModalView.hpp"

DEFINE_TYPE(BSML, ModalView);

namespace BSML {
    void ModalView::Show() {
        this->::HMUI::ModalView::Show(true, moveToCenter, nullptr);
    }

    void ModalView::Hide() {
        this->::HMUI::ModalView::Hide(true, nullptr);
    }

    void ModalView::BlockerClicked() {
        if (onBlockerClicked) {
            il2cpp_utils::RunMethod(host, onBlockerClicked);
        }

        if (dismissOnBlockerClicked) {
            Hide();
        }
    }
}