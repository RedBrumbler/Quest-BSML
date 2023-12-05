#pragma once

#include "BSMLTag.hpp"

namespace BSML {
    class TextTag : public BSMLTag {
        public:
            TextTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject CreateObject(UnityEngine::Transform parent) const override;
    };
}