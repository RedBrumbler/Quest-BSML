#pragma once

#include "TypeHandler.hpp"
#include "../Components/ButtonIconImage.hpp"

namespace BSML {
    class ButtonIconHandler : public TypeHandler<BSML::ButtonIconImage*> {
        public:
            using Base = TypeHandler<BSML::ButtonIconImage*>;
            
            ButtonIconHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
    };
}