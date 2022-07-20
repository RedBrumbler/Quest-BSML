#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "UnityEngine/Vector4.hpp"
#include "UnityEngine/TextAnchor.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/UI/LayoutGroup.hpp"

namespace BSML {
    class LayoutGroupData {
        public:
            LayoutGroupData() {};
            explicit LayoutGroupData(const tinyxml2::XMLElement& elem);
            
            UnityEngine::RectOffset* get_padding() const { if (padding != 0) return UnityEngine::RectOffset::New_ctor(padding, padding, padding, padding); else return UnityEngine::RectOffset::New_ctor(padLeft, padRight, padTop, padBottom); }
            auto get_childAlignment() const { return childAlignment; }
            
            void Apply(UnityEngine::UI::LayoutGroup* layoutGroup) const;
        private:
            int padTop{0};
            int padBottom{0};
            int padLeft{0};
            int padRight{0};
            int padding{0};
            bool hasPadding = false;
            std::optional<UnityEngine::TextAnchor> childAlignment;
    };
}