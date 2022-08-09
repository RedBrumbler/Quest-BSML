#include "BSML/Components/TextPageScrollViewRefresher.hpp"

#include "TMPro/TextMeshProUGUI.hpp"

DEFINE_TYPE(BSML, TextPageScrollViewRefresher);

namespace BSML {
    void TextPageScrollViewRefresher::OnEnable() {
        if (scrollView && Object::IsNativeObjectAlive(scrollView)) {
            scrollView->SetText(scrollView->text ? scrollView->text->get_text() : "");
            scrollView->RefreshButtons();
        }
        
    }

    void TextPageScrollViewRefresher::OnRectTransformDimensionsChange() {
        if (scrollView && Object::IsNativeObjectAlive(scrollView)) {
            scrollView->SetText(scrollView->text ? scrollView->text->get_text() : "");
            scrollView->RefreshButtons();
        }
    }
}