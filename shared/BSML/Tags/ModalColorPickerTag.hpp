#pragma once

#include "BSML/Tags/ModalTag.hpp"
#include "BSML/Data/ModalColorPickerData.hpp"

namespace BSML {
    class ModalColorPickerTag : public ModalTag {
        private:
            using Base = ModalTag;
        public:
            ModalColorPickerTag() : Base() {}
        
            virtual void Construct(UnityEngine::Transform* parent, Il2CppObject* host = nullptr) const override;
        protected:
            friend class ModalColorPickerTagParser;
            virtual void parse(const tinyxml2::XMLElement& elem) override;

            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
            
            ModalColorPickerData modalColorPickerData;
    };
}