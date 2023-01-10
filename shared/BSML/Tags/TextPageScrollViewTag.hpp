#pragma once

#include "BSMLTag.hpp"

namespace BSML {
    class TextPageScrollViewTag : public BSMLTag {
        public:
            TextPageScrollViewTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}
