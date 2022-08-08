#pragma once

#include "BSMLTag.hpp"
#include "UnityEngine/UI/Button.hpp"

namespace BSML {
    class ButtonTag : public BSMLTag {
        public:
            ButtonTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
            virtual UnityEngine::UI::Button* get_buttonPrefab() const;
    };
}