#pragma once

#include "BSMLTag.hpp"

namespace BSML
{
    class ScrollableContainerTag : public BSMLTag {
        public:
            ScrollableContainerTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject *CreateObject(UnityEngine::Transform *parent) const override;
    };
}
