#pragma once

#include "BSML/Tags/BSMLTag.hpp"

namespace BSML {
    class LoadingIndicatorTag : public BSMLTag {
        public:
            LoadingIndicatorTag() : BSMLTag() {}
            
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}