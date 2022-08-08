#pragma once

#include "BSMLTag.hpp"

namespace BSML {
    class IconSegmentedControlTag : public BSMLTag {
        public:
            IconSegmentedControlTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}