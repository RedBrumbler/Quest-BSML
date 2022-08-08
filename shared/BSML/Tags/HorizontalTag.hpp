#pragma once

#include "BSMLTag.hpp"

namespace BSML {
    class HorizontalTag : public BSMLTag {
        public:
            HorizontalTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}