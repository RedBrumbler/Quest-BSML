#pragma once

#include "BSML/Tags/ModalKeyboardTag.hpp"

namespace BSML {
    class StringSettingTag : public ModalKeyboardTag {
        private:
            using Base = ModalKeyboardTag;
        public:
            StringSettingTag() : Base() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}