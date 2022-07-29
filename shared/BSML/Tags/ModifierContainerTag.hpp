#pragma once

#include "BSML/Tags/BSMLTag.hpp"

namespace BSML {
    class ModifierContainerTag : public BSMLTag {
        public:
            ModifierContainerTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}