#pragma once

#include "BSML/Tags/ModalKeyboardTag.hpp"

namespace BSML {
    class StringSettingTag : public ModalKeyboardTag {
        private:
            using Base = ModalKeyboardTag;
        public:
            StringSettingTag() : Base() {}
        
            virtual void Construct(UnityEngine::Transform* parent, Il2CppObject* host = nullptr) const override;
        protected:
            virtual void parse(const tinyxml2::XMLElement& elem) override;

            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}