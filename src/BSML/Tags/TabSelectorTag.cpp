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
    static BSMLNodeParser<TabSelectorTag> tabSelectorTagParser({"tab-select", "tab-selector"});

    HMUI::TextSegmentedControl* get_tabSelectorTagTemplate() {
        static SafePtrUnity<HMUI::TextSegmentedControl> tabSelectorTagTemplate;
        if (!tabSelectorTagTemplate) {
            tabSelectorTagTemplate = Resources::FindObjectsOfTypeAll<HMUI::TextSegmentedControl*>()->FirstOrDefault(
                [](auto x) {
                    auto parent = x->get_transform()->get_parent();
                    if (!parent) return false;
                    if (parent->get_name() != "PlayerStatisticsViewController") return false;
                    return x->_container != nullptr;
                });
        }
        return tabSelectorTagTemplate.ptr();
    }
    UnityEngine::GameObject* TabSelectorTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating TabSelector");
        auto textSegmentedControl = Object::Instantiate(get_tabSelectorTagTemplate(), parent, false);
        textSegmentedControl->dataSource = nullptr;

        auto gameObject = textSegmentedControl->get_gameObject();
        gameObject->set_name("BSMLTabSelector");
        textSegmentedControl->_container = get_tabSelectorTagTemplate()->_container;

        auto transform = gameObject->transform.cast<RectTransform>();
        transform->set_anchoredPosition({0, 0});
        int childCount = transform->get_childCount();
        for (int i = 1; i <= childCount; i++) {
            Object::DestroyImmediate(transform->GetChild(childCount - i)->get_gameObject());
        }

        gameObject->AddComponent<TabSelector*>()->textSegmentedControl = textSegmentedControl;
        gameObject->SetActive(true);

        return gameObject;
    }
}
