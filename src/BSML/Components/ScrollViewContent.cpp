#include "BSML/Components/ScrollViewContent.hpp"

#include "HMUI/ScrollView.hpp"

#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Rect.hpp"

#include "UnityEngine/UI/LayoutRebuilder.hpp"

DEFINE_TYPE(BSML, ScrollViewContent);

namespace BSML {
    void ScrollViewContent::Start() {
        UnityEngine::UI::LayoutRebuilder::ForceRebuildLayoutImmediate(UnityEngine::RectTransform(transform.convert()));
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
        UnityEngine::RectTransform rectTransform {transform.GetChild(0).convert()};
        while (rectTransform.sizeDelta.y == -1) {
            co_yield nullptr;
        }

        while (!scrollView || !scrollView.m_CachedPtr) {
            co_yield nullptr;
        }
        UpdateScrollView();
        co_return;
    }

    void ScrollViewContent::UpdateScrollView() {
        if (!scrollView || !scrollView->m_CachedPtr.m_value) {
            return;
        }

        scrollView.SetContentSize(UnityEngine::RectTransform(transform.GetChild(0).convert()).rect.height);
        scrollView.RefreshButtons();
    }
}
