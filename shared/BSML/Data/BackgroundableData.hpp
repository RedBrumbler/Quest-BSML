#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "UnityEngine/Color.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"

namespace BSML {
    class BackgroundableData {
        public:
            BackgroundableData() {};
            explicit BackgroundableData(const tinyxml2::XMLElement& elem);
            
            auto get_background() const { return background; }
            auto get_backgroundColor() const { return backgroundColor; }

            void Apply(QuestUI::Backgroundable* backgroundable) const;
        private:
            std::string background;
            std::optional<UnityEngine::Color> backgroundColor;
    };
}