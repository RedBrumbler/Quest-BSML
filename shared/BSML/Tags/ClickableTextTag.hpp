#pragma once

#include "BSML/Tags/BSMLTag.hpp"

namespace BSML {
    class ClickableTextTag : public BSMLTag {
        public:
            ClickableTextTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}