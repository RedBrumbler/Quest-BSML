#pragma once

#include "BSMLTag.hpp"

namespace BSML {
    class TextSegmentedControlTag : public BSMLTag {
        public:
            TextSegmentedControlTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject CreateObject(UnityEngine::Transform parent) const override;
    };
}