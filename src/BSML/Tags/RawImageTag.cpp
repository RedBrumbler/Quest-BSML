#include "BSML/Tags/RawImageTag.hpp"
#include "Helpers/getters.hpp"
#include "logging.hpp"

#include "UnityEngine/UI/RawImage.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"

using namespace UnityEngine;

namespace BSML {
    static BSMLNodeParser<RawImageTag> rawImageTagParser({"raw-image", "raw-img"});

    UnityEngine::GameObject RawImageTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating RawImage");
        auto gameObject = GameObject::New_ctor("BSMLRawImage");

        auto image = gameObject.AddComponent<UnityEngine::UI::RawImage>();
        image.material = Helpers::GetUINoGlowMat();
        auto rectTransform = image.rectTransform;
        rectTransform.sizeDelta = {20, 20};
        rectTransform.SetParent(parent, false);

        gameObject.AddComponent<UI::LayoutElement>();
        return gameObject;
    }
}
