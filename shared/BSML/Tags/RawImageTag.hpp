#pragma once

#include "BSMLTag.hpp"

namespace BSML {
    class RawImageTag : public BSMLTag {
        public:
            RawImageTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}