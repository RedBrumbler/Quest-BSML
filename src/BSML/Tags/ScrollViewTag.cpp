#include "BSML/Tags/ScrollViewTag.hpp"
#include "BSML/Components/ScrollView.hpp"
#include "BSML/Components/ExternalComponents.hpp"
#include "BSML/Components/ScrollViewContent.hpp"

#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"
#include "UnityEngine/UI/VerticalLayoutGroup.hpp"
#include "UnityEngine/TextAnchor.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/RectTransform.hpp"

#include "HMUI/TextPageScrollView.hpp"
#include "HMUI/VerticalScrollIndicator.hpp"

#include "TMPro/TextMeshProUGUI.hpp"

#include "GlobalNamespace/ReleaseInfoViewController.hpp"

#include "VRUIControls/VRGraphicRaycaster.hpp"

#include "Helpers/getters.hpp"

namespace BSML {
    static BSMLNodeParser<ScrollViewTag> scrollViewTagParser({"scroll-view"});
    HMUI::TextPageScrollView get_scrollViewTemplate() {
        static SafePtrUnity<HMUI::TextPageScrollView> scrollViewTemplate;
        if (!scrollViewTemplate) {
            scrollViewTemplate = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::ReleaseInfoViewController>().FirstOrDefault()._textPageScrollView.convert();
        }
        return HMUI::TextPageScrollView(scrollViewTemplate.ptr());
    }

    UnityEngine::GameObject ScrollViewTag::CreateObject(UnityEngine::Transform parent) const {
        auto textScrollView = UnityEngine::Object::Instantiate(get_scrollViewTemplate(), parent);
        textScrollView.name = "BSMLScrollView";
        auto pageUpButton = textScrollView.pageUpButton;
        auto pageDownButton = textScrollView.pageDownButton;
        auto verticalScrollIndicator = textScrollView->verticalScrollIndicator;

        UnityEngine::RectTransform* viewport = textScrollView.viewport;
        viewport.gameObject.AddComponent<VRUIControls::VRGraphicRaycaster>().physicsRaycaster = Helpers::GetPhysicsRaycasterWithCache();

        UnityEngine::Object::Destroy(textScrollView.text.gameObject);
        auto gameObject = textScrollView.gameObject;
        UnityEngine::Object::Destroy(textScrollView);
        gameObject.active = false;

        auto scrollView = gameObject.AddComponent<BSML::ScrollView>();
        scrollView.pageUpButton = pageUpButton;
        scrollView.pageDownButton = pageDownButton;
        scrollView.verticalScrollIndicator = verticalScrollIndicator;
        scrollView.viewport = viewport;
        scrollView.platformHelper = Helpers::GetIVRPlatformHelper();

        viewport.anchorMin = UnityEngine::Vector2(0, 0);
        viewport.anchorMax = UnityEngine::Vector2(1, 1);

        UnityEngine::GameObject parentObject = UnityEngine::GameObject::New_ctor();
        parentObject.name = "BSMLScrollViewContent";
        parentObject.transform.SetParent(viewport, false);

        auto contentSize = parentObject.AddComponent<UnityEngine::UI::ContentSizeFitter>();
        contentSize.horizontalFit = UnityEngine::UI::ContentSizeFitter::FitMode::PreferredSize;
        contentSize.verticalFit = UnityEngine::UI::ContentSizeFitter::FitMode::PreferredSize;

        auto verticalLayout = parentObject.AddComponent<UnityEngine::UI::VerticalLayoutGroup>();
        verticalLayout.childForceExpandHeight = false;
        verticalLayout.childForceExpandWidth = false;
        verticalLayout.childControlHeight = true;
        verticalLayout.childControlWidth = true;
        verticalLayout.childAlignment = UnityEngine::TextAnchor::UpperCenter;

        UnityEngine::RectTransform rectTransform {parentObject.transform.convert()};
        rectTransform.anchorMin = UnityEngine::Vector2(0, 1);
        rectTransform.anchorMax = UnityEngine::Vector2(1, 1);
        rectTransform.sizeDelta = UnityEngine::Vector2(0, 0);
        rectTransform.pivot = UnityEngine::Vector2(0.5f, 1);
        parentObject.AddComponent<ScrollViewContent>().scrollView = scrollView;

        auto child = UnityEngine::GameObject::New_ctor();
        child.name = "BSMLScrollViewContentContainer";
        child.transform.SetParent(rectTransform, false);

        auto layoutGroup = child.AddComponent<UnityEngine::UI::VerticalLayoutGroup>();
        layoutGroup.childControlHeight false;
        layoutGroup.childForceExpandHeight false;
        layoutGroup.childAlignment UnityEngine::TextAnchor::LowerCenter;
        layoutGroup.spacing 0.5f;

        auto externalComponents = child.AddComponent<ExternalComponents>();
        externalComponents.Add(scrollView);
        externalComponents.Add(scrollView.transform);
        externalComponents.Add(gameObject.AddComponent<UnityEngine::UI::LayoutElement>());

        UnityEngine::RectTransform(child.transform).sizeDelta = UnityEngine::Vector2(0, -1);

        scrollView._contentRectTransform = UnityEngine::RectTransform(parentObject.transform);
        gameObject.SetActive(true);
        return child;
    }
}
