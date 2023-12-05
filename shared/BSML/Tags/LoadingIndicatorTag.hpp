#pragma once

#include "BSMLTag.hpp"

namespace BSML {
    class LoadingIndicatorTag : public BSMLTag {
        public:
            LoadingIndicatorTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject CreateObject(UnityEngine::Transform parent) const override;
    };
}