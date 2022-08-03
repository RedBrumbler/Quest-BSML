#include "BSML/Tags/ClickableImageTag.hpp"
#include "Helpers/getters.hpp"
#include "logging.hpp"

#include "BSML/Components/ClickableImage.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "HMUI/ImageView.hpp"

using namespace UnityEngine;

namespace BSML {
    static BSMLNodeParser<ClickableImageTag> imageTagParser({"clickable-image", "clickable-img"});
    
    UnityEngine::GameObject* ClickableImageTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating Image");
        auto gameObject = GameObject::New_ctor("BSMLClickableImage");
        auto image = gameObject->AddComponent<ClickableImage*>();
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