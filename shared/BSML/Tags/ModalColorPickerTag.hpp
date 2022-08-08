#pragma once

#include "ModalTag.hpp"

namespace BSML {
    class ModalColorPickerTag : public ModalTag {
        private:
            using Base = ModalTag;
        public:
            ModalColorPickerTag() : Base() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}