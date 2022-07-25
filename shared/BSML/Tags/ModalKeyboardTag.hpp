#pragma once

#include "BSML/Tags/ModalTag.hpp"

namespace BSML {
    class ModalKeyboardTag : public ModalTag {
        public:
            ModalKeyboardTag() : ModalTag() {}
        
            virtual void Construct(UnityEngine::Transform* parent, Il2CppObject* host = nullptr) const override;
        protected:
            friend class ModalKeyboardTagParser;
            virtual void parse(const tinyxml2::XMLElement& elem) override;

            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}