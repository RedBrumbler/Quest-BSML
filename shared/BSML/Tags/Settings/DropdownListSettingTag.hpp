#pragma once

#include "../BSMLTag.hpp"

namespace BSML {
    class DropdownListSettingTag : public BSMLTag {
        public:
            DropdownListSettingTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject CreateObject(UnityEngine::Transform parent) const override;
    };
}
