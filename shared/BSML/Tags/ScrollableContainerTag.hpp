#pragma once

#include "BSML/Tags/BSMLTag.hpp"

namespace BSML
{
    class ScrollableContainerTag : public BSMLTag
    {
        public:
            ScrollableContainerTag() : BSMLTag() {}
    
        protected:
            virtual UnityEngine::GameObject *CreateObject(UnityEngine::Transform *parent) const override;
    };
}
