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

    HMUI::IconSegmentedControl get_iconSegmentedControlTemplate() {
        static SafePtrUnity<HMUI::IconSegmentedControl> iconSegmentedControlTemplate;
        if (!iconSegmentedControlTemplate) {
            iconSegmentedControlTemplate = Resources::FindObjectsOfTypeAll<HMUI::IconSegmentedControl>().FirstOrDefault(
                [](auto x) {
                    if (x.name != "BeatmapCharacteristicSegmentedControl") return false;
                    return x.container != nullptr;
                });
        }
        return HMUI::IconSegmentedControl(iconSegmentedControlTemplate.ptr());
    }

    UnityEngine::GameObject IconSegmentedControlTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating IconSegmentedControl");

        auto iconSegmentedControlTemplate = get_iconSegmentedControlTemplate();
        auto iconSegmentedControl = Object::Instantiate(iconSegmentedControlTemplate, parent, false);
        iconSegmentedControl.dataSource = HMUI::IconSegmentedControl::IDataSource{nullptr};

        auto gameObject = iconSegmentedControl.gameObject;
        gameObject.name = "BSMLIconSegmentedControl";
        iconSegmentedControl._container = iconSegmentedControlTemplate._container;

        RectTransform transform {gameObject.transform.convert()};
        transform.anchoredPosition = {0, 0};
        int childCount = transform.childCount;
        for (int i = 1; i <= childCount; i++) {
            Object::DestroyImmediate(transform.GetChild(childCount - i).gameObject);
        }

        Object::Destroy(gameObject.GetComponent<GlobalNamespace::BeatmapCharacteristicSegmentedControlController>());
        gameObject.SetActive(true);
        return gameObject;
    }
}
