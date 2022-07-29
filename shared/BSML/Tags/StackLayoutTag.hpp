#pragma once

#include "BSML/Tags/BSMLTag.hpp"

namespace BSML {
    class StackLayoutTag : public BSMLTag {
        public:
            StackLayoutTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}