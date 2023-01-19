#pragma once

#include "BSMLTag.hpp"

namespace BSML {
    class ProgressBarTag : public BSMLTag {
        private:
            using Base = BSMLTag;
        public:
            ProgressBarTag() : Base() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform *parent) const override;
    };
}
