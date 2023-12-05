#include "BSML/Tags/BackgroundTag.hpp"
#include "logging.hpp"

#include "BSML/Components/Backgroundable.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLNodeParser<BackgroundTag> backgroundTagParser({"background", "bg", "div"});
    UnityEngine::GameObject BackgroundTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating Background");
        auto gameObject = GameObject::New_ctor("BSMLBackground");
        gameObject.transform.SetParent(parent, false);
        gameObject.AddComponent<ContentSizeFitter>();
        gameObject.AddComponent<Backgroundable>();

        RectTransform rectTransform {gameObject.transform.convert()};
        rectTransform.anchorMin = {0, 0};
        rectTransform.anchorMax = {1, 1};
        rectTransform.sizeDelta = {0, 0};

        return gameObject;
    }
}
