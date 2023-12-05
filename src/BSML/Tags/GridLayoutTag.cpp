#include "BSML/Tags/GridLayoutTag.hpp"
#include "BSML/Components/Backgroundable.hpp"
#include "logging.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/UI/GridLayoutGroup.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLNodeParser<GridLayoutTag> gridLayoutTagParser({"grid"});
    UnityEngine::GameObject GridLayoutTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating GridLayout");
        auto gameObject = GameObject::New_ctor("BSMLGridLayoutGroup");
        gameObject.transform.SetParent(parent, false);
        auto grid = gameObject.AddComponent<GridLayoutGroup>();

        auto contentSizeFitter = gameObject.AddComponent<ContentSizeFitter>();
        contentSizeFitter.verticalFit = ContentSizeFitter::FitMode::PreferredSize;
        gameObject.AddComponent<Backgroundable>();

        auto rectTransform = grid.rectTransform;
        rectTransform.anchorMin = {0, 0};
        rectTransform.anchorMax = {1, 1};
        rectTransform.sizeDelta = {0, 0};

        gameObject.AddComponent<LayoutElement>();
        return gameObject;
    }
}
