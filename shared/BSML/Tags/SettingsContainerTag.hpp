#pragma once

#include "BSMLTag.hpp"
#include "ScrollViewTag.hpp"

namespace BSML {
    class SettingsContainerTag : public ScrollViewTag {
        public:
            SettingsContainerTag() : ScrollViewTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}