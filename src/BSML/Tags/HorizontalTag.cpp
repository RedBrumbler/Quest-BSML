#include "BSML/Tags/HorizontalTag.hpp"
#include "BSML/Components/Backgroundable.hpp"
#include "logging.hpp"
#include "internal_macros.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/UI/HorizontalLayoutGroup.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLTagParser<HorizontalTag> horizontalTagParser({"horizontal"});
    void HorizontalTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        auto go = CreateObject(parent);
        auto horizontal = go->GetComponent<UnityEngine::UI::HorizontalLayoutGroup*>();
        SetHostField(host, horizontal);
        
        backgroundableData.Apply(go->GetComponent<BSML::Backgroundable*>());
        contentSizeFitterData.Apply(go->GetComponent<UnityEngine::UI::ContentSizeFitter*>());
        horizontalOrVerticalLayoutGroupData.Apply(horizontal);
        layoutElementData.Apply(go->GetComponent<UnityEngine::UI::LayoutElement*>());
        layoutGroupData.Apply(horizontal);
        rectTransformData.Apply(horizontal->get_rectTransform());

        CreateChildren(go->get_transform(), host);
    }

    UnityEngine::GameObject* HorizontalTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating Horizontal");
        auto gameObject = GameObject::New_ctor("BSMLHorizontalLayoutGroup");
        gameObject->get_transform()->SetParent(parent, false);
        auto horizontal = gameObject->AddComponent<HorizontalLayoutGroup*>();

        auto contentSizeFitter = gameObject->AddComponent<ContentSizeFitter*>();
        contentSizeFitter->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
        gameObject->AddComponent<Backgroundable*>();

        auto rectTransform = horizontal->get_rectTransform();
        rectTransform->set_anchorMin({0, 0});
        rectTransform->set_anchorMax({1, 1});
        rectTransform->set_sizeDelta({0, 0});

        gameObject->AddComponent<LayoutElement*>();
        return gameObject;
    }

    void HorizontalTag::parse(const tinyxml2::XMLElement& elem) {
        DEBUG("Parsing horizontal tag");
        this->::BSML::BSMLTag::parse(elem);
        
        backgroundableData = BackgroundableData(elem);
        contentSizeFitterData = ContentSizeFitterData(elem);
        horizontalOrVerticalLayoutGroupData = HorizontalOrVerticalLayoutGroupData(elem);
        layoutElementData = LayoutElementData(elem);
        layoutGroupData = LayoutGroupData(elem);
        rectTransformData = RectTransformData(elem);
    }
}