#include "BSML/Tags/VerticalTag.hpp"
#include "logging.hpp"

#include "BSML/Components/Backgroundable.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/UI/VerticalLayoutGroup.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLNodeParser<VerticalTag> verticalTagParser({"vertical"});
    UnityEngine::GameObject VerticalTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating Vertical");
        auto gameObject = GameObject::New_ctor("BSMLVerticalLayoutGroup");
        gameObject.transform.SetParent(parent, false);
        auto horizontal = gameObject.AddComponent<VerticalLayoutGroup>();

        auto contentSizeFitter = gameObject.AddComponent<ContentSizeFitter>();
        contentSizeFitter.horizontalFit = ContentSizeFitter::FitMode::PreferredSize;
        gameObject.AddComponent<Backgroundable>();

        auto rectTransform = horizontal.rectTransform;
        rectTransform.anchorMin = {0, 0};
        rectTransform.anchorMax = {1, 1};
        rectTransform.sizeDelta = {0, 0};

        gameObject.AddComponent<LayoutElement>();
        return gameObject;
    }
}
