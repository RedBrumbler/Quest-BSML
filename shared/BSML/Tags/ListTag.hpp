#pragma once

#include "BSMLTag.hpp"

namespace BSML {
    class ListTag : public BSMLTag {
        public:
            ListTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject CreateObject(UnityEngine::Transform parent) const override;
    };
}