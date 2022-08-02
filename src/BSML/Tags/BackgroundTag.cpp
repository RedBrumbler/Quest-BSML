#include "BSML/Tags/BackgroundTag.hpp"
#include "logging.hpp"
#include "internal_macros.hpp"

#include "BSML/Components/Backgroundable.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLTagParser<BackgroundTag> backgroundTagParser({"background", "bg", "div"});
    void BackgroundTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        auto go = CreateObject(parent);
        auto background = go->GetComponent<Backgroundable*>();
        SetHostField(host, background);
        
        CreateChildren(go->get_transform(), host);
    }

    UnityEngine::GameObject* BackgroundTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating Background");
        auto gameObject = GameObject::New_ctor("BSMLBackground");
        gameObject->get_transform()->SetParent(parent, false);
        gameObject->AddComponent<ContentSizeFitter*>();
        gameObject->AddComponent<Backgroundable*>();

        auto rectTransform = reinterpret_cast<RectTransform*>(gameObject->get_transform());
        rectTransform->set_anchorMin({0, 0});
        rectTransform->set_anchorMax({1, 1});
        rectTransform->set_sizeDelta({0, 0});

        return gameObject;
    }
    
    void BackgroundTag::parse(const tinyxml2::XMLElement& elem) {
        DEBUG("Parsing background tag");
        this->::BSML::BSMLTag::parse(elem);
    }
}