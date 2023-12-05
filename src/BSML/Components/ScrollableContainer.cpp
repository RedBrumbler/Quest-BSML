#include "BSML/Components/ScrollableContainer.hpp"
#include "Helpers/delegates.hpp"
#include "logging.hpp"

#include "HMUI/ButtonBinder.hpp"
#include "HMUI/VerticalScrollIndicator.hpp"
#include "HMUI/ItemForFocussedScrolling.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Rect.hpp"
#include "UnityEngine/Time.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/UI/Button.hpp"

DEFINE_TYPE(BSML, ScrollableContainer);

using namespace UnityEngine;
using namespace UnityEngine::UI;

template<typename T>
T lerp(T a, T b, float t) {
    return a + (b - a) * t;
}

template<typename T>
T min(T a, T b) {
    return (a < b) * a + (a >= b) * b;
}

template<typename T>
T max(T a, T b) {
    return (a > b) * a + (a <= b) * b;
}

template<typename T>
T abs(T v) {
    return v * ((v > 0) - (v < 0));
}

namespace BSML {
    void ScrollableContainer::UpdateViewPortMask() {
        auto img = viewport.GetComponent<Image>();
        if (img) {
            img.enabled = maskOverflow;
        }
    }

    void ScrollableContainer::Awake() {
        buttonBinder = HMUI::ButtonBinder::New_ctor();

        RefreshContent();
        RefreshBindings();
        runScrollAnim = false;
    }

    void ScrollableContainer::RefreshBindings() {
        if (!buttonBinder) {
            ERROR("No button binder");
            return;
        }

        buttonBinder.ClearBindings();
        if (pageUpButton) {
            if (!upButtonAction)
                upButtonAction = MakeSystemAction(convert(), il2cpp_functions::class_get_method_from_name(il2cpp_functions::object_get_class(convert()), "PageUpButtonPressed", 0));
            buttonBinder.AddBinding(pageUpButton, upButtonAction);
        }
        if (pageDownButton) {
            if (!downButtonAction)
                downButtonAction = MakeSystemAction(convert(), il2cpp_functions::class_get_method_from_name(il2cpp_functions::object_get_class(convert()), "PageDownButtonPressed", 0));
            buttonBinder.AddBinding(pageDownButton, downButtonAction);
        }
    }

    void ScrollableContainer::RefreshContent() {
        SetContentSize(contentRectTransform.rect.height);
        contentHeight = contentRectTransform.rect.height;
        RefreshBindings();
        ComputeScrollFocusPosY();
    }

    void ScrollableContainer::RefreshButtons() {
        if (pageUpButton) {
            pageUpButton.interactable = destinationPos > 0;
        }
        if (pageDownButton) {
            pageDownButton.interactable = (destinationPos < contentHeight - (viewport ? viewport.rect.height : 0));
        }
    }

    void ScrollableContainer::ContentSizeUpdated() {
        RefreshContent();
        RefreshButtons();
        this->ScrollTo(scrollToBottomOnUpdate ? std::numeric_limits<float>::max() : 0, false);
    }

    void ScrollableContainer::Update() {
        auto height = contentRectTransform.rect.height;
        if (contentHeight != height && height > 0.0f)
            ContentSizeUpdated();

        if (runScrollAnim) {
            float num = lerp(contentRectTransform.anchoredPosition.y, destinationPos, Time::get_deltaTime() * smooth);
            if (abs(num - destinationPos) < 0.01f)
            {
                num = destinationPos;
                runScrollAnim = false;
            }

            contentRectTransform.anchoredPosition = {0, num};
            UpdateVerticalScrollIndicator(num);
        }
    }

    void ScrollableContainer::ComputeScrollFocusPosY() {
        auto componentsInChildren = GetComponentsInChildren<HMUI::ItemForFocussedScrolling>(true);
        scrollFocusPositions = ArrayW<float>(il2cpp_array_size_t(componentsInChildren.size()));

        int i = 0;
        for (auto comp : componentsInChildren) {
            scrollFocusPositions[i] = WorldPositionToScrollViewPosition(comp.transform.position).y;
            i++;
        }

        std::sort(scrollFocusPositions.begin(), scrollFocusPositions.end(), [](float a, float b) {
            return a < b;
        });
    }

    void ScrollableContainer::UpdateVerticalScrollIndicator(float posY) {
        if (verticalScrollIndicator) {
            auto progress = posY / (contentHeight - viewport.rect.height);
            verticalScrollIndicator.progress = progress;
        }
    }

    void ScrollableContainer::ScrollDown(bool animated) {
        this->ScrollTo(maxPosition, animated);
    }

    void ScrollableContainer::ScrollToWorldPosition(UnityEngine::Vector3 worldPosition, float pageRelativePosition, bool animated) {
        float num = WorldPositionToScrollViewPosition(worldPosition).y;
        num -= pageRelativePosition * scrollPageHeight;
        ScrollTo(num, animated);
    }

    void ScrollableContainer::ScrollToWorldPositionIfOutsideArea(UnityEngine::Vector3 worldPosition, float pageRelativePosition, float relativeBoundaryStart, float relativeBoundaryEnd, bool animated) {
        float num = WorldPositionToScrollViewPosition(worldPosition).y;
        float scrollPageHeight = this->scrollPageHeight;
        float num2 = destinationPos + relativeBoundaryStart * scrollPageHeight;
        float num3 = destinationPos + relativeBoundaryEnd * scrollPageHeight;
        if (num > num2 && num < num3)
        {
            return;
        }
        num -= pageRelativePosition * scrollPageHeight;
        ScrollTo(num, animated);
    }

    void ScrollableContainer::ScrollToNormalized(float dstPosY, bool animated) {
        ScrollTo(std::clamp(dstPosY, 0.0f, 1.0f) * get_maxPosition(), animated);
    }

    void ScrollableContainer::ScrollTo(float dstPosY, bool animated) {
        SetDestinationPosY(dstPosY);
        if (!animated)
            contentRectTransform.anchoredPosition = {0.0f, destinationPos};
        RefreshButtons();
        runScrollAnim = true;
    }

    void ScrollableContainer::PageUpButtonPressed() {
        float num = destinationPos;
        switch (scrollType)
        {
            case ScrollType::PageSize:
                num -= pageStepNormalizedSize * scrollPageHeight;
                break;
            case ScrollType::FixedCellSize:
                num -= fixedCellSize * (float)(floor(scrollPageHeight / fixedCellSize) - 1);
                num = (float)floor(num / fixedCellSize) * fixedCellSize;
                break;
            case ScrollType::FocusItems:
                {
                    float threshold = destinationPos + scrollItemRelativeThresholdPosition * scrollPageHeight;

                    float max = destinationPos;
                    for (auto posy : scrollFocusPositions) {
                        if (posy >= threshold) continue;
                        if (posy > max) max = posy;
                    }
                    num = max;
                    num -= pageStepNormalizedSize * scrollPageHeight;
                    break;
                }
        }

        ScrollTo(num, true);
        RefreshButtons();
        set_enabled(true);
    }

    void ScrollableContainer::PageDownButtonPressed() {
        float num = destinationPos;
        switch (scrollType)
        {
            case ScrollType::PageSize:
                num += pageStepNormalizedSize * scrollPageHeight;
                break;
            case ScrollType::FixedCellSize:
                num += fixedCellSize * (float)(ceil(scrollPageHeight / fixedCellSize) - 1);
                num = (float)ceil(num / fixedCellSize) * fixedCellSize;
                break;
            case ScrollType::FocusItems:
                {
                    float threshold = destinationPos + (1.0f - scrollItemRelativeThresholdPosition) * scrollPageHeight;
                    float min = destinationPos + scrollPageHeight;
                    for (auto posy : scrollFocusPositions) {
                        if (posy <= threshold) continue;
                        if (posy < min) min = posy;
                    }
                    num = min;
                    num -= (1.0f - pageStepNormalizedSize) * scrollPageHeight;
                    break;
                }
        }

        ScrollTo(num, true);
        RefreshButtons();
        enabled = true;
    }

    void ScrollableContainer::SetDestinationPosY(float value) {
        float maxPosition = this->maxPosition;
        if (maxPosition < 0 && !alignBottom) maxPosition = 0.0f;
        destinationPos = min(maxPosition, max(0.0f, value));
    }

    bool ScrollableContainer::get_alignBottom() {
        return _alignBottom;
    }

    void ScrollableContainer::set_alignBottom(bool value) {
        _alignBottom = value;
        this->ScrollTo(destinationPos, true);
    }

    bool ScrollableContainer::get_maskOverflow() {
        return _maskOverflow;
    }

    void ScrollableContainer::set_maskOverflow(bool value) {
        _maskOverflow = value;
        UpdateViewPortMask();
    }

    float ScrollableContainer::get_scrollPageHeight() {
        return viewport ? viewport.rect.height : 0.0f;
    }

    float ScrollableContainer::get_maxPosition() {
        return contentHeight - viewport.rect.height;
    }
}
