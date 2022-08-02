#pragma once

#include "BSML/Tags/BSMLTag.hpp"

namespace BSML {
    class GridLayoutTag : public BSMLTag {
        public:
            GridLayoutTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}