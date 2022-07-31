#include "BSML/Tags/TabSelectorTag.hpp"
#include "logging.hpp"

#include "BSML/Components/TabSelector.hpp"
#include "HMUI/TextSegmentedControl.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"

using namespace UnityEngine;

namespace BSML {
    static BSMLTagParser<TabSelectorTag> tabSelectorTagParser({"tab-select", "tab-selector"});

    HMUI::TextSegmentedControl* tabSelectorTagTemplate = nullptr;
    UnityEngine::GameObject* TabSelectorTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating TabSelector");
        if (!tabSelectorTagTemplate || !Object::IsNativeObjectAlive(tabSelectorTagTemplate)) {
            tabSelectorTagTemplate = Resources::FindObjectsOfTypeAll<HMUI::TextSegmentedControl*>().FirstOrDefault(
                [](auto x) { 
                    auto parent = x->get_transform()->get_parent();
                    if (!parent) return false;
                    if (parent->get_name() != "PlayerStatisticsViewController") return false;
                    return x->container != nullptr;
                });
        }

        auto textSegmentedControl = Object::Instantiate(tabSelectorTagTemplate, parent, false);
        textSegmentedControl->dataSource = nullptr;

        auto gameObject = textSegmentedControl->get_gameObject();
        gameObject->set_name("BSMLTabSelector");
        textSegmentedControl->container = tabSelectorTagTemplate->container;

        auto transform = reinterpret_cast<RectTransform*>(gameObject->get_transform());
        transform->set_anchoredPosition({0, 0});
        int childCount = transform->get_childCount();
        for (int i = 0; i < childCount; i++) {
            // as we destroy children, the count goes down, so if we keep getting child 0 we get all of them
            Object::Destroy(transform->GetChild(0)->get_gameObject());
        }

        gameObject->AddComponent<TabSelector*>()->textSegmentedControl = textSegmentedControl;
        gameObject->SetActive(true);
        
        return gameObject;
    }
}