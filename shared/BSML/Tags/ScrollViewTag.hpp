#pragma once

#include "BSML/Tags/BSMLTag.hpp"

namespace BSML {
    class ScrollViewTag : public BSMLTag {
        public:
            using Base = BSMLTag;
            ScrollViewTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}