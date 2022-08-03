#include "BSML/Tags/StackLayoutTag.hpp"
#include "logging.hpp"


#include "BSML/Components/Backgroundable.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"
#include "HMUI/StackLayoutGroup.hpp"

using namespace UnityEngine;

namespace BSML {
    static BSMLNodeParser<StackLayoutTag> stackLayoutTagParser({"stack"});

    UnityEngine::GameObject* StackLayoutTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating StackLayoutTag");
        auto gameObject = GameObject::New_ctor("BSMLStackLayoutGroup");
        gameObject->get_transform()->SetParent(parent, false);
        gameObject->AddComponent<HMUI::StackLayoutGroup*>();
        gameObject->AddComponent<UI::ContentSizeFitter*>();
        gameObject->AddComponent<Backgroundable*>();

        auto rectTransform = reinterpret_cast<RectTransform*>(gameObject->get_transform());
        rectTransform->set_anchorMin({0, 0});
        rectTransform->set_anchorMax({1, 1});
        rectTransform->set_sizeDelta({0, 0});
        
        gameObject->AddComponent<UI::LayoutElement*>();
        return gameObject;
    }
}