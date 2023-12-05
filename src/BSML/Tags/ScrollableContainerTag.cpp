#include "BSML/Tags/ScrollableContainerTag.hpp"
#include "Helpers/getters.hpp"
#include "Helpers/utilities.hpp"

#include "BSML/Components/ScrollableContainer.hpp"
#include "BSML/Components/ExternalComponents.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/UI/Mask.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/UI/VerticalLayoutGroup.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "HMUI/ImageView.hpp"
#include "HMUI/Touchable.hpp"
#include "HMUI/EventSystemListener.hpp"
#include "VRUIControls/VRGraphicRaycaster.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLNodeParser<ScrollableContainerTag> scrollableContainerTagParser({"scrollable-container"});

    UnityEngine::GameObject ScrollableContainerTag::CreateObject(UnityEngine::Transform parent) const {
        auto go = GameObject::New_ctor("BSMLScrollableContainer");
        go.SetActive(false);

        auto transform = go.AddComponent<RectTransform>();
        transform.SetParent(parent, false);
        transform.localPosition = {0, 0, 0};
        transform.anchorMin = {0, 0};
        transform.anchorMax = {1, 1};
        transform.anchoredPosition = {0, 0};
        transform.sizeDelta = {0, 0};

        auto vpgo = GameObject::New_ctor("Viewport");
        auto viewport = vpgo.AddComponent<RectTransform>();
        viewport.SetParent(transform, false);
        viewport.localPosition = {0, 0, 0};
        viewport.anchorMin = {0, 0};
        viewport.anchorMax = {1, 1};
        viewport.anchoredPosition = {0, 0};
        viewport.sizeDelta = {0, 0};

        auto vpMask = vpgo.AddComponent<Mask>();
        auto vpImage = vpgo.AddComponent<HMUI::ImageView>();
        vpMask.showMaskGraphic = false;
        vpImage.color = {1, 1, 1, 1};
        vpImage.sprite = Utilities::ImageResources::GetWhitePixel();
        vpImage.material = Helpers::GetUINoGlowMat();

        auto contentGo = GameObject::New_ctor("Content Wrapper");
        auto content = contentGo.AddComponent<RectTransform>();
        content.SetParent(viewport, false);
        content.localPosition = {0, 0, 0};
        content.anchorMin = {0, 1};
        content.anchorMax = {1, 1};
        content.anchoredPosition = {0, 0};
        content.sizeDelta = {0, 0};
        content.pivot = {0.5, 1};

        auto contentFitter = contentGo.AddComponent<ContentSizeFitter>();
        contentFitter.horizontalFit = ContentSizeFitter::FitMode::Unconstrained;
        contentFitter.verticalFit = ContentSizeFitter::FitMode::PreferredSize;

        auto layout = contentGo.AddComponent<VerticalLayoutGroup>();
        layout.childControlHeight = false;
        layout.childForceExpandHeight = false;
        layout.childForceExpandWidth = false;

        go.AddComponent<HMUI::Touchable>(); // Required by EventSystemListener
        go.AddComponent<HMUI::EventSystemListener>(); // Required by ScrollView
        auto scrollView = go.AddComponent<ScrollableContainer>();
        scrollView._contentRectTransform = content;
        scrollView.viewport = viewport;
        scrollView._platformHelper = Helpers::GetIVRPlatformHelper();

        auto externalComponents = contentGo.AddComponent<ExternalComponents>();
        externalComponents.Add(scrollView);
        externalComponents.Add(transform);
        auto layoutElement = go.AddComponent<LayoutElement>();
        layoutElement.minWidth = -1;
        layoutElement.preferredWidth = -1;
        layoutElement.flexibleWidth = 0;

        externalComponents.Add(layoutElement);

        go.SetActive(true);
        return contentGo;
    }
}
