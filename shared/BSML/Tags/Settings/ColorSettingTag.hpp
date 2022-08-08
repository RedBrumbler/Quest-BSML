#pragma once

#include "../ModalColorPickerTag.hpp"

namespace BSML {
    class ColorSettingTag : public ModalColorPickerTag {
        private:
            using Base = ModalColorPickerTag;
        public:
            ColorSettingTag() : Base() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}