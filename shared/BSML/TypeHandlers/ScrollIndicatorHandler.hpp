#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "BSML/Components/ScrollIndicator.hpp"

namespace BSML {
    class ScrollIndicatorHandler : public TypeHandler<ScrollIndicator*> {
        public:
            using Base = TypeHandler<BSML::ScrollIndicator*>;
            ScrollIndicatorHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
    };
}