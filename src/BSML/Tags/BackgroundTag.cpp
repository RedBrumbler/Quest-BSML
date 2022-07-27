#include "BSML/Tags/BackgroundTag.hpp"
#include "logging.hpp"
#include "internal_macros.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    void BackgroundTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        auto go = CreateObject(parent);
        auto background = go->GetComponent<Backgroundable*>();
        SetHostField(host, background);
        
        backgroundableData.Apply(go->GetComponent<BSML::Backgroundable*>());
        contentSizeFitterData.Apply(go->GetComponent<UnityEngine::UI::ContentSizeFitter*>());
        rectTransformData.Apply(reinterpret_cast<RectTransform*>(background->get_transform()));
        
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

        backgroundableData = BackgroundableData(elem);
        contentSizeFitterData = ContentSizeFitterData(elem);
        rectTransformData = RectTransformData(elem);
    }
}