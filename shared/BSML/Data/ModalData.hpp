#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "UnityEngine/Vector2.hpp"
#include "BSML/Components/ModalView.hpp"

namespace BSML {
    class ModalData {
        public:
            ModalData() {};
            explicit ModalData(const tinyxml2::XMLElement& elem);
            
            auto get_clickOffCloses() const { return clickOffCloses; }
            auto get_moveToCenter() const { return moveToCenter; }
            auto get_onBlockerClicked() const { return onBlockerClicked; }

            void Apply(BSML::ModalView* modalView, Il2CppObject* host) const;
        private:
            std::optional<bool> clickOffCloses;
            std::optional<bool> moveToCenter;
            std::string onBlockerClicked;
    };
}