#pragma once

#include "BSML/Tags/BSMLTag.hpp"

namespace BSML {
    class ClickableImageTag : public BSMLTag {
        public:
            ClickableImageTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}