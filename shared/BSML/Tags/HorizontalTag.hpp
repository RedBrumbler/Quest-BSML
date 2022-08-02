#pragma once

#include "BSML/Tags/BSMLTag.hpp"

namespace BSML {
    class HorizontalTag : public BSMLTag {
        public:
            HorizontalTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}