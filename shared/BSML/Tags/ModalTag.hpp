#pragma once

#include "BSMLTag.hpp"

namespace BSML {
    class ModalTag : public BSMLTag {
        public:
            ModalTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}