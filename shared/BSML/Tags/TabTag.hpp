#pragma once

#include "BackgroundTag.hpp"

namespace BSML {
    class TabTag : public BackgroundTag {
        public:
            using Base = BackgroundTag;
            TabTag() : BackgroundTag() {}
        protected:
            virtual UnityEngine::GameObject CreateObject(UnityEngine::Transform parent) const override;
    };
}