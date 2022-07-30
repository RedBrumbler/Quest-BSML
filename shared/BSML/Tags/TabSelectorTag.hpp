#pragma once

#include "BSML/Tags/BSMLTag.hpp"

namespace BSML {
    class TabSelectorTag : public BSMLTag {
        public:
            TabSelectorTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}