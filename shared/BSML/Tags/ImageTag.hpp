#pragma once

#include "BSML/Tags/BSMLTag.hpp"

namespace BSML {
    class ImageTag : public BSMLTag {
        public:
            ImageTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}