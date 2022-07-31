#pragma once

#include "BSML/Tags/ModalColorPickerTag.hpp"

namespace BSML {
    class ColorSettingTag : public ModalColorPickerTag {
        private:
            using Base = ModalColorPickerTag;
        public:
            ColorSettingTag() : Base() {}
        
            virtual void Construct(UnityEngine::Transform* parent, Il2CppObject* host = nullptr) const override;
        protected:
            virtual void parse(const tinyxml2::XMLElement& elem) override;

            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}