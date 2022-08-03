#pragma once

#include "BSML/Tags/BSMLTag.hpp"
#include "BSML/Tags/ScrollViewTag.hpp"

namespace BSML {
    class SettingsContainerTag : public ScrollViewTag {
        public:
            SettingsContainerTag() : ScrollViewTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}