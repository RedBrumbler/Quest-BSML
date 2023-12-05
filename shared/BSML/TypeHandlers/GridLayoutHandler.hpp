#pragma once

#include "TypeHandler.hpp"
#include "UnityEngine/UI/GridLayoutGroup.hpp"

namespace BSML {
    class GridLayoutHandler : public TypeHandler<UnityEngine::UI::GridLayoutGroup> {
        public:
            using Base = TypeHandler<UnityEngine::UI::GridLayoutGroup>;
            GridLayoutHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
    };
}
