#pragma once

#include "BSMLTag.hpp"
#include "HMUI/InputFieldView.hpp"

namespace BSML {
    class TextFieldTag : public BSMLTag {
        public:
            TextFieldTag() : BSMLTag() {}
        protected:
            virtual HMUI::InputFieldView* get_fieldViewPrefab() const;
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}
