#include "BSML/Tags/VerticalTag.hpp"
#include "logging.hpp"
#include "internal_macros.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/UI/VerticalLayoutGroup.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    void VerticalTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        auto go = CreateObject(parent);
        auto vertical = go->GetComponent<UnityEngine::UI::VerticalLayoutGroup*>();
        SetHostField(host, vertical);
        
        backgroundableData.Apply(go->GetComponent<BSML::Backgroundable*>());
        contentSizeFitterData.Apply(go->GetComponent<UnityEngine::UI::ContentSizeFitter*>());
        horizontalOrVerticalLayoutGroupData.Apply(vertical);
        layoutElementData.Apply(go->GetComponent<UnityEngine::UI::LayoutElement*>());
        layoutGroupData.Apply(vertical);
        rectTransformData.Apply(vertical->get_rectTransform());
        
        CreateChildren(go->get_transform(), host);
    }

    UnityEngine::GameObject* VerticalTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating Vertical");
        auto gameObject = GameObject::New_ctor("BSMLVerticalLayoutGroup");
        gameObject->get_transform()->SetParent(parent, false);
        auto horizontal = gameObject->AddComponent<VerticalLayoutGroup*>();

        auto contentSizeFitter = gameObject->AddComponent<ContentSizeFitter*>();
        contentSizeFitter->set_horizontalFit(ContentSizeFitter::FitMode::PreferredSize);
        gameObject->AddComponent<Backgroundable*>();

        auto rectTransform = horizontal->get_rectTransform();
        rectTransform->set_anchorMin({0, 0});
        rectTransform->set_anchorMax({1, 1});
        rectTransform->set_sizeDelta({0, 0});

        gameObject->AddComponent<LayoutElement*>();
        return gameObject;
    }
    
    void VerticalTag::parse(const tinyxml2::XMLElement& elem) {
        DEBUG("Parsing vertical tag");
        this->::BSML::BSMLTag::parse(elem);

        backgroundableData = BackgroundableData(elem);
        contentSizeFitterData = ContentSizeFitterData(elem);
        horizontalOrVerticalLayoutGroupData = HorizontalOrVerticalLayoutGroupData(elem);
        layoutElementData = LayoutElementData(elem);
        layoutGroupData = LayoutGroupData(elem);
        rectTransformData = RectTransformData(elem);
    }
}