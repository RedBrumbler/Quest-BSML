#pragma once

#include "TypeHandler.hpp"
#include "../Components/TextGradientUpdater.hpp"

namespace BSML {
    class TextGradientUpdaterHandler : public TypeHandler<BSML::TextGradientUpdater*> {
        public:
            using Base = TypeHandler<BSML::TextGradientUpdater*>;
            TextGradientUpdaterHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
    };
}