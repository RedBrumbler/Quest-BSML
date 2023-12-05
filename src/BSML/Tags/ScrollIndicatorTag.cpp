#include "BSML/Tags/ScrollIndicatorTag.hpp"
#include "logging.hpp"

#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Object.hpp"
#include "HMUI/VerticalScrollIndicator.hpp"
#include "BSML/Components/ScrollIndicator.hpp"
#include "UnityEngine/RectTransform.hpp"

using namespace UnityEngine;

namespace BSML {
    static BSMLNodeParser<ScrollIndicatorTag> scrollIndicatorTagParser({"scroll-indicator", "vertical-scroll-indicator"});

    HMUI::VerticalScrollIndicator get_scrollIndicatorTemplate() {
        static SafePtrUnity<HMUI::VerticalScrollIndicator> scrollIndicatorTemplate;
        if (!scrollIndicatorTemplate)
        {
            scrollIndicatorTemplate = UnityEngine::Resources::FindObjectsOfTypeAll<HMUI::VerticalScrollIndicator>().FirstOrDefault();
        }
        return HMUI::VerticalScrollIndicator(scrollIndicatorTemplate.ptr());
    }

    UnityEngine::GameObject ScrollIndicatorTag::CreateObject(UnityEngine::Transform parent) const
    {
        DEBUG("making ScrollIndicator");
        auto gameObj = UnityEngine::Object::Instantiate(get_scrollIndicatorTemplate().gameObject, parent, false);
        DEBUG("instantiated {}", gameObj.name);

        gameObj.SetActive(false);
        gameObj.name = "BSMLVerticalScrollIndicator";

        RectTransform transform {gameObj.transform.convert()};
        transform.SetParent(parent, false);

        UnityEngine::Object::DestroyImmediate(gameObj.GetComponent<HMUI::VerticalScrollIndicator>());

        auto indicator = gameObj.AddComponent<BSML::ScrollIndicator>();
        indicator.Handle = UnityEngine::RectTransform(transform.GetChild(0).transform.convert());

        gameObj.SetActive(true);

        return gameObj;
    }
}
