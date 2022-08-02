#include "BSML/Components/ScrollViewContent.hpp"

#include "HMUI/ScrollView.hpp"

#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Rect.hpp"

#include "UnityEngine/UI/LayoutRebuilder.hpp"

DEFINE_TYPE(BSML, ScrollViewContent);

namespace BSML {

    HMUI::ScrollView* scrollView = nullptr;
    bool dirty = false;

    void ScrollViewContent::Start() {
        UnityEngine::UI::LayoutRebuilder::ForceRebuildLayoutImmediate(reinterpret_cast<UnityEngine::RectTransform*>(get_transform()));
        StopAllCoroutines();
        StartCoroutine(custom_types::Helpers::CoroutineHelper::New(SetupScrollView()));

    }

    void ScrollViewContent::OnEnable() {
        UpdateScrollView();
    }

    void ScrollViewContent::OnRectTransformDimensionsChange() {
        dirty = true;
    }

    void ScrollViewContent::Update() {
        if (dirty) {
            dirty = false;
            UpdateScrollView();
        }
    }

    custom_types::Helpers::Coroutine ScrollViewContent::SetupScrollView() {
        UnityEngine::RectTransform* rectTransform = reinterpret_cast<UnityEngine::RectTransform*>(get_transform()->GetChild(0));
        while (rectTransform->get_sizeDelta().y == -1) {
            co_yield nullptr;
        }
        UpdateScrollView();
        co_return;
    }

    void ScrollViewContent::UpdateScrollView() {
        scrollView->SetContentSize(reinterpret_cast<UnityEngine::RectTransform*>(get_transform()->GetChild(0))->get_rect().get_height());
        scrollView->RefreshButtons();
    }
}