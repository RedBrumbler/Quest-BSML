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
    static BSMLNodeParser<IconSegmentedControlTag> iconSegmentedControlTag({"icon-segments"});
    
    HMUI::IconSegmentedControl* get_iconSegmentedControlTemplate() {
        static SafePtrUnity<HMUI::IconSegmentedControl> iconSegmentedControlTemplate;
        if (!iconSegmentedControlTemplate) {
            iconSegmentedControlTemplate = Resources::FindObjectsOfTypeAll<HMUI::IconSegmentedControl*>().FirstOrDefault(
                [](auto x) { 
                    auto name = x->get_name();
                    if (name != "BeatmapCharacteristicSegmentedControl") return false;
                    return x->container != nullptr;
                });
        }
        return iconSegmentedControlTemplate.ptr();
    }

    UnityEngine::GameObject* IconSegmentedControlTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating IconSegmentedControl");

        auto iconSegmentedControlTemplate = get_iconSegmentedControlTemplate();
        auto iconSegmentedControl = Object::Instantiate(iconSegmentedControlTemplate, parent, false);
        iconSegmentedControl->dataSource = nullptr;

        auto gameObject = iconSegmentedControl->get_gameObject();
        gameObject->set_name("BSMLIconSegmentedControl");
        iconSegmentedControl->container = iconSegmentedControlTemplate->container;
        
        auto transform = reinterpret_cast<RectTransform*>(gameObject->get_transform());
        transform->set_anchoredPosition({0, 0});
        int childCount = transform->get_childCount();
        for (int i = 1; i <= childCount; i++) {
            Object::DestroyImmediate(transform->GetChild(childCount - i)->get_gameObject());
        }

        Object::Destroy(gameObject->GetComponent<GlobalNamespace::BeatmapCharacteristicSegmentedControlController*>());
        gameObject->SetActive(true);
        return gameObject;
    }
}