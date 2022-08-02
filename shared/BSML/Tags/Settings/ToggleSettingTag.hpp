#pragma once

#include "BSML/Tags/BSMLTag.hpp"

namespace BSML {
    class ToggleSettingTag : public BSMLTag {
        public:
            ToggleSettingTag() : BSMLTag() {}
        
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}