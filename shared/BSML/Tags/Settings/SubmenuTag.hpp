#pragma once

#include "BSML/Tags/BSMLTag.hpp"

namespace BSML {
    class SubmenuTag : public BSMLTag {
        public:
            SubmenuTag() : BSMLTag() {}
        
            virtual void Construct(UnityEngine::Transform* parent, Il2CppObject* host = nullptr) const override;
        protected:
            virtual void parse(const tinyxml2::XMLElement& elem) override;

            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}