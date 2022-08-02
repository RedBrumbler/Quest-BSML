#pragma once

#include "BSML/Tags/BSMLTag.hpp"

namespace BSML {
    class PageButtonTag : public BSMLTag {
        public:
            PageButtonTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}