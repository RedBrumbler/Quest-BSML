#pragma once

#include "BSML/Tags/BSMLTag.hpp"

#include "BSML/Data/RectTransformData.hpp"
#include "BSML/Data/LayoutGroupData.hpp"
#include "BSML/Data/ContentSizeFitterData.hpp"
#include "BSML/Data/LayoutElementData.hpp"

namespace BSML
{
    class ScrollIndicatorTag : public BSMLTag
    {
    public:
        ScrollIndicatorTag() : BSMLTag() {}

        virtual void Construct(UnityEngine::Transform *parent, Il2CppObject *host = nullptr) const override;

    protected:
        friend class ScrollIndicatorTagParser;
        virtual void parse(const tinyxml2::XMLElement &elem) override;

        virtual UnityEngine::GameObject *CreateObject(UnityEngine::Transform *parent) const override;
    };
}
