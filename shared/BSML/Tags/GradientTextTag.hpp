#pragma once

#include "TextTag.hpp"

namespace BSML {
    class GradientTextTag : public TextTag {
        public:
            GradientTextTag() : TextTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}