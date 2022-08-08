#pragma once

#include "BSMLTag.hpp"

namespace BSML {
    class VerticalTag : public BSMLTag {
        public:
            VerticalTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}
