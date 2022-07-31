#pragma once

#include "BSML/Tags/ButtonTag.hpp"

namespace BSML {
    class PrimaryButtonTag : public ButtonTag {
        private:
            using Base = ButtonTag;
        public:
            PrimaryButtonTag() : Base() {}
        protected:
            virtual UnityEngine::UI::Button* get_buttonPrefab() const override;
    };
}