#include "BSML/Tags/VerticalTag.hpp"
#include "logging.hpp"
#include "BSMLMacros.hpp"

#include "UnityEngine/GameObject.hpp"
#include "questui/shared/BeatSaberUI.hpp"

using namespace QuestUI::BeatSaberUI;

namespace BSML {
    void VerticalTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        auto go = CreateObject(parent);
        SetHostField(host, go->GetComponent<UnityEngine::UI::VerticalLayoutGroup*>());
        
        CreateChildren(go->get_transform(), host);
    }

    UnityEngine::GameObject* VerticalTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating Vertical");
        auto vertical = CreateVerticalLayoutGroup(parent);
        auto gameObject = vertical->get_gameObject();
        if (backgroundableData.get_background() != "")
            backgroundableData.Apply(gameObject->GetComponent<QuestUI::Backgroundable*>());
        
        contentSizeFitterData.Apply(gameObject->GetComponent<UnityEngine::UI::ContentSizeFitter*>());
        horizontalOrVerticalLayoutGroupData.Apply(vertical);
        layoutElementData.Apply(gameObject->GetComponent<UnityEngine::UI::LayoutElement*>());
        layoutGroupData.Apply(vertical);
        rectTransformData.Apply(vertical->get_rectTransform());

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