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

    HMUI::IconSegmentedControl get_verticalIconSegmentedControlTemplate() {
        static SafePtrUnity<HMUI::IconSegmentedControl> verticalIconSegmentedControlTemplate;
        if (!verticalIconSegmentedControlTemplate) {
            auto vc = Resources::FindObjectsOfTypeAll<GlobalNamespace::PlatformLeaderboardViewController>().FirstOrDefault();
            verticalIconSegmentedControlTemplate = vc._scopeSegmentedControl;
        }
        return HMUI::IconSegmentedControl(verticalIconSegmentedControlTemplate.ptr());
    }

    UnityEngine::GameObject VerticalIconSegmentedControlTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating VerticalIconSegmentedControl");
        auto verticalIconSegmentedControlTemplate = get_verticalIconSegmentedControlTemplate();
        auto verticalIconSegmentedControl = Object::Instantiate(verticalIconSegmentedControlTemplate, parent, false);
        verticalIconSegmentedControl.dataSource = HMUI::SegmentedControl::IDataSource{nullptr};

        auto gameObject = verticalIconSegmentedControl.gameObject;
        gameObject.name = "BSMLVerticalIconSegmentedControl";
        verticalIconSegmentedControl._container = verticalIconSegmentedControlTemplate._container;

        RectTransform transform {gameObject.transform.convert()};
        transform.anchorMin = {0.5f, 0.5f};
        transform.anchorMax = {0.5f, 0.5f};
        transform.anchoredPosition = {0, 0};
        transform.pivot = {0.5f, 0.5f};

        int childCount = transform.childCount;
        for (int i = 1; i <= childCount; i++) {
            Object::DestroyImmediate(transform.GetChild(childCount - i).gameObject);
        }

        gameObject.SetActive(true);
        return gameObject;
    }
}
