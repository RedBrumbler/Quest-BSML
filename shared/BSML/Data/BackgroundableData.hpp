#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "UnityEngine/Color.hpp"
#include "BSML/Components/Backgroundable.hpp"

namespace BSML {
    class BackgroundableData {
        public:
            BackgroundableData() {};
            explicit BackgroundableData(const tinyxml2::XMLElement& elem);
            
            auto get_background() const { return background; }
            auto get_backgroundColor() const { return backgroundColor; }
            auto get_backgroundColor0() const { return backgroundColor0; }
            auto get_backgroundColor1() const { return backgroundColor1; }

            void Apply(BSML::Backgroundable* backgroundable) const;
        private:
            std::string background;
            std::optional<UnityEngine::Color> backgroundColor;
            std::optional<UnityEngine::Color> backgroundColor0;
            std::optional<UnityEngine::Color> backgroundColor1;
    };
}