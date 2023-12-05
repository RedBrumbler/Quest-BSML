#pragma once

#include "BSMLTag.hpp"

namespace BSML {
    class ModifierTag : public BSMLTag {
        public:
            ModifierTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject CreateObject(UnityEngine::Transform parent) const override;
    };
}