#include "BSML/Components/TextPageScrollViewRefresher.hpp"

#include "TMPro/TextMeshProUGUI.hpp"

DEFINE_TYPE(BSML, TextPageScrollViewRefresher);

namespace BSML {
    void TextPageScrollViewRefresher::OnEnable() {
        if (scrollView && scrollView.m_CachedPtr) {
            scrollView.SetText(scrollView.text ? scrollView.text.text : "");
            scrollView.RefreshButtons();
        }

    }

    void TextPageScrollViewRefresher::OnRectTransformDimensionsChange() {
        if (scrollView && scrollView.m_CachedPtr) {
            scrollView.SetText(scrollView.text ? scrollView.text.text : "");
            scrollView.RefreshButtons();
        }
    }
}
