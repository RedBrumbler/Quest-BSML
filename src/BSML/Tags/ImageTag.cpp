#include "BSML/Tags/ImageTag.hpp"
#include "Helpers/getters.hpp"
#include "logging.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "HMUI/ImageView.hpp"

using namespace UnityEngine;

namespace BSML {
    static BSMLTagParser<ImageTag> imageTagParser({"image", "img"});
    
    UnityEngine::GameObject* ImageTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating Image");
        auto gameObject = GameObject::New_ctor("BSMLImage");
        auto image = gameObject->AddComponent<HMUI::ImageView*>();
        image->set_material(Helpers::GetUINoGlowMat());
        auto rectTransform = image->get_rectTransform();
        rectTransform->set_sizeDelta({20, 20});
        rectTransform->SetParent(parent, false);
        // TODO: blank sprite
        //image->set_sprite(BlankSprite);

        gameObject->AddComponent<UI::LayoutElement*>();
        return gameObject;
    }
}