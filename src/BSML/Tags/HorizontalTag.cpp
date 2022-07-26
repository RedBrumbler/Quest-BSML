#include "BSML/Tags/HorizontalTag.hpp"
#include "logging.hpp"
#include "internal_macros.hpp"

#include "UnityEngine/GameObject.hpp"
#include "questui/shared/BeatSaberUI.hpp"

using namespace QuestUI::BeatSaberUI;

namespace BSML {
    void HorizontalTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        auto go = CreateObject(parent);
        SetHostField(host, go->GetComponent<UnityEngine::UI::HorizontalLayoutGroup*>());
        
        CreateChildren(go->get_transform(), host);
    }

    UnityEngine::GameObject* HorizontalTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating Horizontal");
        auto horizontal = CreateHorizontalLayoutGroup(parent);
        auto gameObject = horizontal->get_gameObject();
        
        gameObject->AddComponent<BSML::Backgroundable*>();
        backgroundableData.Apply(gameObject->GetComponent<BSML::Backgroundable*>());
        
        contentSizeFitterData.Apply(gameObject->GetComponent<UnityEngine::UI::ContentSizeFitter*>());
        horizontalOrVerticalLayoutGroupData.Apply(horizontal);
        layoutElementData.Apply(gameObject->GetComponent<UnityEngine::UI::LayoutElement*>());
        layoutGroupData.Apply(horizontal);
        rectTransformData.Apply(horizontal->get_rectTransform());

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