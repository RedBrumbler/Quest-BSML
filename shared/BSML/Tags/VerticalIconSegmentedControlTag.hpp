#pragma once

#include "BSMLTag.hpp"

namespace BSML {
    class VerticalIconSegmentedControlTag : public BSMLTag {
        public:
            VerticalIconSegmentedControlTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject CreateObject(UnityEngine::Transform parent) const override;
    };
}