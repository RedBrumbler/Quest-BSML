#pragma once

#include "BSMLTag.hpp"

namespace BSML {
    class ButtonWithIconTag : public BSMLTag {
        public:
            ButtonWithIconTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject CreateObject(UnityEngine::Transform parent) const override;
    };
}