#include "BSML/Tags/ScrollIndicatorTag.hpp"
#include "logging.hpp"

#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Object.hpp"
#include "HMUI/VerticalScrollIndicator.hpp"
#include "BSML/Components/ScrollIndicator.hpp"
#include "UnityEngine/RectTransform.hpp"

namespace BSML
{
    HMUI::VerticalScrollIndicator *scrollIndicator = nullptr;

    static BSMLTagParser<ScrollIndicatorTag> scrollIndicatorTagParser({"scroll-indicator", "vertical-scroll-indicator"});

    UnityEngine::GameObject *ScrollIndicatorTag::CreateObject(UnityEngine::Transform *parent) const
    {
        DEBUG("making ScrollIndicator");
        if (!scrollIndicator || !UnityEngine::Object::IsNativeObjectAlive(scrollIndicator))
        {
            scrollIndicator = UnityEngine::Resources::FindObjectsOfTypeAll<HMUI::VerticalScrollIndicator *>().FirstOrDefault();
        }

        auto gameObj = UnityEngine::Object::Instantiate(scrollIndicator->get_gameObject(), parent, false);
        DEBUG("instantiated {}", gameObj->get_name());

        gameObj->SetActive(false);
        gameObj->set_name("BSMLVerticalScrollIndicator");
        
        auto transform = gameObj->GetComponent<UnityEngine::RectTransform *>();
        transform->SetParent(parent, false);
        

        UnityEngine::Object::DestroyImmediate(gameObj->GetComponent<HMUI::VerticalScrollIndicator*>());
    
        auto indicator = gameObj->AddComponent<BSML::ScrollIndicator*>();
        indicator->set_Handle(transform->GetChild(0)->GetComponent<UnityEngine::RectTransform*>());

        gameObj->SetActive(true);
    
        return gameObj;
    }
}