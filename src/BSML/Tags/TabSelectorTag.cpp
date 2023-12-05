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

    HMUI::TextSegmentedControl get_tabSelectorTagTemplate() {
        static SafePtrUnity<HMUI::TextSegmentedControl> tabSelectorTagTemplate;
        if (!tabSelectorTagTemplate) {
            tabSelectorTagTemplate = Resources::FindObjectsOfTypeAll<HMUI::TextSegmentedControl>().FirstOrDefault(
                [](auto x) {
                    auto parent = x.transform.parent;
                    if (!parent) return false;
                    if (parent.name != "PlayerStatisticsViewController") return false;
                    return x.container != nullptr;
                });
        }
        return HMUI::TextSegmentedControl(tabSelectorTagTemplate.ptr());
    }

    UnityEngine::GameObject TabSelectorTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating TabSelector");
        auto tabSelectorTagTemplate = get_tabSelectorTagTemplate();
        auto textSegmentedControl = Object::Instantiate(tabSelectorTagTemplate, parent, false);
        textSegmentedControl.dataSource = HMUI::SegmentedControl::IDataSource(nullptr);

        auto gameObject = textSegmentedControl.gameObject;
        gameObject.name = "BSMLTabSelector";
        textSegmentedControl._container = tabSelectorTagTemplate._container;

        RectTransform transform {gameObject.transform.convert()};
        transform.anchoredPosition = {0, 0};
        int childCount = transform.childCount;
        for (int i = 1; i <= childCount; i++) {
            Object::DestroyImmediate(transform.GetChild(childCount - i).gameObject);
        }

        gameObject.AddComponent<TabSelector>().textSegmentedControl = textSegmentedControl;
        gameObject.SetActive(true);

        return gameObject;
    }
}
