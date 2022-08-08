#pragma once

#include "BSML/Components/ScrollIndicator.hpp"
#include "TypeHandler.hpp"

namespace BSML {
    class ScrollIndicatorHandler : public TypeHandler<BSML::ScrollIndicator*> {
        public:
            using Base = TypeHandler<BSML::ScrollIndicator*>;
            ScrollIndicatorHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
    };
}