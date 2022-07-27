#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/UI/GridLayoutGroup.hpp"

namespace BSML {
    class GridLayoutGroupData {
        public:
            GridLayoutGroupData() {};
            explicit GridLayoutGroupData(const tinyxml2::XMLElement& elem);
            
            auto get_spacingX() const { return spacingX; };
            auto get_spacingY() const { return spacingY; };
            auto get_cellSizeX() const { return cellSizeX; };
            auto get_cellSizeY() const { return cellSizeY; };

            void Apply(UnityEngine::UI::GridLayoutGroup* gridLayoutGroup) const;
        private:
            std::optional<float> spacingX;
            std::optional<float> spacingY;
            std::optional<float> cellSizeX;
            std::optional<float> cellSizeY;
    };
}