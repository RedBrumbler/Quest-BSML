#include "BSML/Tags/IconSegmentedControlTag.hpp"
#include "logging.hpp"

#include "BSML/Components/TabSelector.hpp"
#include "HMUI/IconSegmentedControl.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "GlobalNamespace/BeatmapCharacteristicSegmentedControlController.hpp"

using namespace UnityEngine;

namespace BSML {
    static BSMLTagParser<IconSegmentedControlTag> iconSegmentedControlTag({"icon-segments"});
    
    HMUI::IconSegmentedControl* iconSegmentedControlTemplate = nullptr;

    UnityEngine::GameObject* IconSegmentedControlTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating IconSegmentedControl");
        if (!iconSegmentedControlTemplate || !Object::IsNativeObjectAlive(iconSegmentedControlTemplate)) {
            iconSegmentedControlTemplate = Resources::FindObjectsOfTypeAll<HMUI::IconSegmentedControl*>().FirstOrDefault(
                [](auto x) { 
                    auto name = x->get_name();
                    if (name != "BeatmapCharacteristicSegmentedControl") return false;
                    return x->container != nullptr;
                });
        }

        auto iconSegmentedControl = Object::Instantiate(iconSegmentedControlTemplate, parent, false);
        iconSegmentedControl->dataSource = nullptr;

        auto gameObject = iconSegmentedControl->get_gameObject();
        gameObject->set_name("BSMLIconSegmentedControl");
        iconSegmentedControl->container = iconSegmentedControlTemplate->container;
        
        auto transform = reinterpret_cast<RectTransform*>(gameObject->get_transform());
        transform->set_anchoredPosition({0, 0});
        int childCount = transform->get_childCount();
        for (int i = 0; i < childCount; i++) {
            // as we destroy children, the count goes down, so if we keep getting child 0 we get all of them
            Object::Destroy(transform->GetChild(0)->get_gameObject());
        }

        Object::Destroy(gameObject->GetComponent<GlobalNamespace::BeatmapCharacteristicSegmentedControlController*>());
        gameObject->SetActive(true);
        return gameObject;
    }
}