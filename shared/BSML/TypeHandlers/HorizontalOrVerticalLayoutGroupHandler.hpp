#pragma once

#include "TypeHandler.hpp"
#include "UnityEngine/UI/HorizontalOrVerticalLayoutGroup.hpp"

namespace BSML {
    class HorizontalOrVerticalLayoutGroupHandler : public TypeHandler<UnityEngine::UI::HorizontalOrVerticalLayoutGroup> {
        public:
            using Base = TypeHandler<UnityEngine::UI::HorizontalOrVerticalLayoutGroup>;
            HorizontalOrVerticalLayoutGroupHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
    };
}
