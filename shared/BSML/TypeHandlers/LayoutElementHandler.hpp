#pragma once

#include "TypeHandler.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"

namespace BSML {
    class LayoutElementHandler : public TypeHandler<UnityEngine::UI::LayoutElement> {
        public:
            using Base = TypeHandler<UnityEngine::UI::LayoutElement>;
            LayoutElementHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
    };
}
