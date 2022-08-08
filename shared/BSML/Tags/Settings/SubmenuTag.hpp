#pragma once

#include "../BSMLTag.hpp"

namespace BSML {
    class SubmenuTag : public BSMLTag {
        public:
            SubmenuTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}