#include "BSML/Components/TextPageScrollViewRefresher.hpp"

DEFINE_TYPE(BSML, TextPageScrollViewRefresher);

namespace BSML {
    void TextPageScrollViewRefresher::OnEnable() {
        if (scrollView) {
            scrollView->SetText(scrollView->text);
            scrollView->RefreshButtons();
        }
        
    }

    void TextPageScrollViewRefresher::OnRectTransformDimensionsChange() {
        if (scrollView) {
            scrollView->SetText(scrollView->text);
            scrollView->RefreshButtons();
        }
    }
}