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
    static BSMLTagParser<ScrollViewTag> scrollViewTagParser({"scroll-view"});

    HMUI::TextPageScrollView* scrollViewTemplate = nullptr;

    UnityEngine::GameObject* ScrollViewTag::CreateObject(UnityEngine::Transform* parent) const {
        if (!scrollViewTemplate || !UnityEngine::Object::IsNativeObjectAlive(scrollViewTemplate)) {
            scrollViewTemplate = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::ReleaseInfoViewController*>().FirstOrDefault()->textPageScrollView;
        }

        HMUI::TextPageScrollView* textScrollView = UnityEngine::Object::Instantiate(scrollViewTemplate, parent);
        textScrollView->set_name("BSMLScrollView");
        UnityEngine::UI::Button* pageUpButton = textScrollView->pageUpButton;
        UnityEngine::UI::Button* pageDownButton = textScrollView->pageDownButton;
        HMUI::VerticalScrollIndicator* verticalScrollIndicator = textScrollView->verticalScrollIndicator;

        UnityEngine::RectTransform* viewport = textScrollView->viewport;
        viewport->get_gameObject()->AddComponent<VRUIControls::VRGraphicRaycaster*>()->physicsRaycaster = Helpers::GetPhysicsRaycasterWithCache();

        UnityEngine::Object::Destroy(textScrollView->text->get_gameObject());
        UnityEngine::GameObject* gameObject = textScrollView->get_gameObject();
        UnityEngine::Object::Destroy(textScrollView);
        gameObject->set_active(false);

        BSML::ScrollView* scrollView = gameObject->AddComponent<BSML::ScrollView*>();
        scrollView->pageUpButton = pageUpButton;
        scrollView->pageDownButton = pageDownButton;
        scrollView->verticalScrollIndicator = verticalScrollIndicator;
        scrollView->viewport = viewport;
        scrollView->platformHelper = Helpers::GetIVRPlatformHelper();

        viewport->set_anchorMin(UnityEngine::Vector2(0, 0));
        viewport->set_anchorMax(UnityEngine::Vector2(1, 1));

        UnityEngine::GameObject* parentObject = UnityEngine::GameObject::New_ctor();
        parentObject->set_name("BSMLScrollViewContent");
        parentObject->get_transform()->SetParent(viewport, false);

        UnityEngine::UI::ContentSizeFitter* contentSize = parentObject->AddComponent<UnityEngine::UI::ContentSizeFitter*>();
        contentSize->set_horizontalFit(UnityEngine::UI::ContentSizeFitter::FitMode::PreferredSize);
        contentSize->set_verticalFit(UnityEngine::UI::ContentSizeFitter::FitMode::PreferredSize);

        UnityEngine::UI::VerticalLayoutGroup* verticalLayout = parentObject->AddComponent<UnityEngine::UI::VerticalLayoutGroup*>();
        verticalLayout->set_childForceExpandHeight(false);
        verticalLayout->set_childForceExpandWidth(false);
        verticalLayout->set_childControlHeight(true);
        verticalLayout->set_childControlWidth(true);
        verticalLayout->set_childAlignment(UnityEngine::TextAnchor::UpperCenter);

        UnityEngine::RectTransform* rectTransform = reinterpret_cast<UnityEngine::RectTransform*>(parentObject->get_transform());
        rectTransform->set_anchorMin(UnityEngine::Vector2(0, 1));
        rectTransform->set_anchorMax(UnityEngine::Vector2(1, 1));
        rectTransform->set_sizeDelta(UnityEngine::Vector2(0, 0));
        rectTransform->set_pivot(UnityEngine::Vector2(0.5f, 1));
        parentObject->AddComponent<ScrollViewContent*>()->scrollView = scrollView;

        UnityEngine::GameObject* child = UnityEngine::GameObject::New_ctor();
        child->set_name("BSMLScrollViewContentContainer");
        child->get_transform()->SetParent(rectTransform, false);

        UnityEngine::UI::VerticalLayoutGroup* layoutGroup = child->AddComponent<UnityEngine::UI::VerticalLayoutGroup*>();
        layoutGroup->set_childControlHeight(false);
        layoutGroup->set_childForceExpandHeight(false);
        layoutGroup->set_childAlignment(UnityEngine::TextAnchor::LowerCenter);
        layoutGroup->set_spacing(0.5f);

        auto externalComponents = child->AddComponent<ExternalComponents*>();
        externalComponents->components->Add(scrollView);
        externalComponents->components->Add(scrollView->get_transform());
        externalComponents->components->Add(gameObject->AddComponent<UnityEngine::UI::LayoutElement*>());

        reinterpret_cast<UnityEngine::RectTransform*>(child->get_transform())->set_sizeDelta(UnityEngine::Vector2(0, -1));

        scrollView->contentRectTransform = reinterpret_cast<UnityEngine::RectTransform*>(parentObject->get_transform());
        gameObject->SetActive(true);
        return child;
    }
}