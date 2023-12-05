#include "BSML/Tags/ModifierContainerTag.hpp"
#include "logging.hpp"

#include "BSML/Components/Backgroundable.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/UI/VerticalLayoutGroup.hpp"
#include "UnityEngine/RectOffset.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLNodeParser<ModifierContainerTag> modifierContainerTagParser({"modifier-container"});

    UnityEngine::GameObject ModifierContainerTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating ModifierContainer");

        auto gameObject = GameObject::New_ctor("BSMLModifierContainer");
        gameObject.transform.SetParent(parent, false);

        auto vertical = gameObject.AddComponent<VerticalLayoutGroup>();
        vertical.padding = RectOffset::New_ctor(3, 3, 2, 2);
        vertical.childControlHeight = false;
        vertical.childForceExpandHeight = false;

        gameObject.AddComponent<ContentSizeFitter>().verticalFit = ContentSizeFitter::FitMode::PreferredSize;
        // I saw that this one was not there on pc, but I want people to be able to use it anyways, it doesn't do anything unless you tell it to anyways
        gameObject.AddComponent<Backgroundable>();

        auto rectTransform = vertical.rectTransform;
        rectTransform.anchoredPosition = {0, 3};
        rectTransform.anchorMin = {0.5f, 0.5f};
        rectTransform.anchorMax = {0.5f, 0.5f};
        rectTransform.sizeDelta = {54, 3};

        gameObject.AddComponent<LayoutElement>();
        return gameObject;
    }
}
