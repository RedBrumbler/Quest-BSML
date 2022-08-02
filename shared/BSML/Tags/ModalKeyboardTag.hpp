#pragma once

#include "BSML/Tags/ModalTag.hpp"

namespace BSML {
    class ModalKeyboardTag : public ModalTag {
        public:
            ModalKeyboardTag() : ModalTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}