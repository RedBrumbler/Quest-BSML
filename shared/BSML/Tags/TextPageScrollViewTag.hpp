#pragma once

#include "BSML/Tags/BSMLTag.hpp"

using namespace UnityEngine;

namespace BSML {
    class TextPageScrollViewTag : public BSMLTag {
        public:
            TextPageScrollViewTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}