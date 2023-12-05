#pragma once

#include "BSMLTag.hpp"

namespace BSML {
    class BackgroundTag : public BSMLTag {
        public:
            BackgroundTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject CreateObject(UnityEngine::Transform parent) const override;
    };
}
