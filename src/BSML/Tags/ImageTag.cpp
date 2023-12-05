#include "BSML/Tags/ImageTag.hpp"
#include "Helpers/getters.hpp"
#include "Helpers/utilities.hpp"
#include "logging.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "HMUI/ImageView.hpp"

using namespace UnityEngine;

namespace BSML {
    static BSMLNodeParser<ImageTag> imageTagParser({"image", "img"});

    UnityEngine::GameObject ImageTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating Image");
        auto gameObject = GameObject::New_ctor("BSMLImage");
        auto image = gameObject.AddComponent<HMUI::ImageView>();
        image.material = Helpers::GetUINoGlowMat();
        auto rectTransform = image.rectTransform;
        rectTransform.sizeDelta = {20, 20};
        rectTransform.SetParent(parent, false);
        // TODO: maybe use a default placeholder sprite instead? maybe a BSML image
        image.sprite = Utilities::ImageResources::GetBlankSprite();

        gameObject.AddComponent<UI::LayoutElement>();
        return gameObject;
    }
}
