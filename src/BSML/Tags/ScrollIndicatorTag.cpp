#include "BSML/Tags/ScrollIndicatorTag.hpp"
#include "logging.hpp"

#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Object.hpp"
#include "HMUI/VerticalScrollIndicator.hpp"

namespace BSML
{
    HMUI::VerticalScrollIndicator *ScrollIndicator = nullptr;

    void ScrollIndicatorTag::Construct(UnityEngine::Transform *parent, Il2CppObject *host) const
    {
        auto obj = CreateObject(parent);

        ConstructChildren(parent, host);
    }

    UnityEngine::GameObject *ScrollIndicatorTag::CreateObject() const
    {
        DEBUG("making ScrollIndicator");
        if (!ScrollIndicator || !Object::IsNativeObjectAlive(ScrollIndicator))
        {
            ScrollIndicator = Resources::FindObjectsOfTypeAll<VerticalScrollIndicator *>().FirstOrDefault([](auto x)
                                                                                                          { return x->get_name() == "VerticalScrollIndicator" });
        }

        auto baseObj = Object::Instantiate(ScrollIndicator);
        auto gameObj = baseObj->get_gameObject();

        gameObj->SetActive(false);

        return obj;
    }

    void ScrollIndicatorTag::parse(const tinyxml2::XMLElement &elem)
    {
        DEBUG("Parsing ScrollIndicator tag.");
        this->Base::parse(elem);

        base
    }
}