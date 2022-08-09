#include "BSML/Tags/VerticalIconSegmentedControlTag.hpp"
#include "logging.hpp"

#include "HMUI/IconSegmentedControl.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "GlobalNamespace/BeatmapCharacteristicSegmentedControlController.hpp"
#include "GlobalNamespace/PlatformLeaderboardViewController.hpp"

using namespace UnityEngine;

namespace BSML {
    static BSMLNodeParser<VerticalIconSegmentedControlTag> vericalIconSegmentedControlTag({"vertical-icon-segments"});
    
    HMUI::IconSegmentedControl* get_verticalIconSegmentedControlTemplate() {
        static SafePtrUnity<HMUI::IconSegmentedControl> verticalIconSegmentedControlTemplate;
        if (!verticalIconSegmentedControlTemplate) {
            auto vc = Resources::FindObjectsOfTypeAll<GlobalNamespace::PlatformLeaderboardViewController*>().FirstOrDefault();
            verticalIconSegmentedControlTemplate = vc->scopeSegmentedControl;
        }
        return verticalIconSegmentedControlTemplate.ptr();
    }

    UnityEngine::GameObject* VerticalIconSegmentedControlTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating VerticalIconSegmentedControl");
        auto verticalIconSegmentedControlTemplate = get_verticalIconSegmentedControlTemplate();
        auto verticalIconSegmentedControl = Object::Instantiate(verticalIconSegmentedControlTemplate, parent, false);
        verticalIconSegmentedControl->dataSource = nullptr;

        auto gameObject = verticalIconSegmentedControl->get_gameObject();
        gameObject->set_name("BSMLVerticalIconSegmentedControl");
        verticalIconSegmentedControl->container = verticalIconSegmentedControlTemplate->container;
        
        auto transform = reinterpret_cast<RectTransform*>(gameObject->get_transform());
        transform->set_anchorMin({0.5f, 0.5f});
        transform->set_anchorMax({0.5f, 0.5f});
        transform->set_anchoredPosition({0, 0});
        transform->set_pivot({0.5f, 0.5f});

        int childCount = transform->get_childCount();
        for (int i = 0; i < childCount; i++) {
            // as we destroy children, the count goes down, so if we keep getting child 0 we get all of them
            Object::Destroy(transform->GetChild(0)->get_gameObject());
        }

        gameObject->SetActive(true);
        return gameObject;
    }
}