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

    HMUI::TextSegmentedControl* textSegmentedControlTemplate = nullptr;

    UnityEngine::GameObject* TextSegmentedControlTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating TextSegmentedControl");
        if (!textSegmentedControlTemplate || !Object::IsNativeObjectAlive(textSegmentedControlTemplate)) {
            textSegmentedControlTemplate = Resources::FindObjectsOfTypeAll<HMUI::TextSegmentedControl*>().FirstOrDefault(
                [](auto x) { 
                    auto name = x->get_name();
                    if (name != "BeatmapDifficultySegmentedControl") return false;
                    return x->container != nullptr;
                });
        }

        auto textSegmentedControl = Object::Instantiate(textSegmentedControlTemplate, parent, false);
        textSegmentedControl->dataSource = nullptr;

        auto gameObject = textSegmentedControl->get_gameObject();
        gameObject->set_name("BSMLTextSegmentedControl");
        textSegmentedControl->container = textSegmentedControlTemplate->container;
        
        auto transform = reinterpret_cast<RectTransform*>(gameObject->get_transform());
        transform->set_anchoredPosition({0, 0});
        int childCount = transform->get_childCount();
        for (int i = 0; i < childCount; i++) {
            // as we destroy children, the count goes down, so if we keep getting child 0 we get all of them
            Object::Destroy(transform->GetChild(0)->get_gameObject());
        }

        Object::Destroy(gameObject->GetComponent<GlobalNamespace::BeatmapDifficultySegmentedControlController*>());
        gameObject->SetActive(true);
        return gameObject;
    }
}