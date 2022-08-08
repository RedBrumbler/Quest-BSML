#pragma once

#include "BSMLTag.hpp"

namespace BSML
{
    class ScrollIndicatorTag : public BSMLTag {
    public:
        ScrollIndicatorTag() : BSMLTag() {}
    protected:
        virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform *parent) const override;
    };
}
