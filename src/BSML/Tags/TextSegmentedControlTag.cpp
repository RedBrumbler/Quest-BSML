#include "BSML/Tags/TextSegmentedControlTag.hpp"
#include "logging.hpp"

#include "BSML/Components/TabSelector.hpp"
#include "HMUI/TextSegmentedControl.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "GlobalNamespace/BeatmapDifficultySegmentedControlController.hpp"

using namespace UnityEngine;

namespace BSML {
    static BSMLNodeParser<TextSegmentedControlTag> textSegmentedControlTag({"text-segments"});

    HMUI::TextSegmentedControl get_textSegmentedControlTemplate() {
        SafePtrUnity<HMUI::TextSegmentedControl> textSegmentedControlTemplate;
        if (!textSegmentedControlTemplate) {
            textSegmentedControlTemplate = Resources::FindObjectsOfTypeAll<HMUI::TextSegmentedControl>().FirstOrDefault(
                [](auto x) {
                    if (x.name != "BeatmapDifficultySegmentedControl") return false;
                    return x.container != nullptr;
                });
        }
        return HMUI::TextSegmentedControl(textSegmentedControlTemplate.ptr());
    }

    UnityEngine::GameObject TextSegmentedControlTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating TextSegmentedControl");

        auto textSegmentedControlTemplate = get_textSegmentedControlTemplate();
        auto textSegmentedControl = Object::Instantiate(textSegmentedControlTemplate, parent, false);
        textSegmentedControl.dataSource = HMUI::SegmentedControl::IDataSource(nullptr);

        auto gameObject = textSegmentedControl.gameObject;
        gameObject.name = "BSMLTextSegmentedControl";
        textSegmentedControl._container = textSegmentedControlTemplate._container;

        RectTransform transform {gameObject.transform.convert()};
        transform.anchoredPosition = {0, 0};
        int childCount = transform.childCount;
        for (int i = 1; i <= childCount; i++) {
            Object::DestroyImmediate(transform.GetChild(childCount - i).gameObject);
        }

        Object::Destroy(gameObject.GetComponent<GlobalNamespace::BeatmapDifficultySegmentedControlController>());
        gameObject.SetActive(true);
        return gameObject;
    }
}
