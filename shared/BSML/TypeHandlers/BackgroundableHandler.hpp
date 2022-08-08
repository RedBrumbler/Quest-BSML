#pragma once

#include "TypeHandler.hpp"
#include "BSML/Components/Backgroundable.hpp"

namespace BSML {
    class BackgroundableHandler : public TypeHandler<Backgroundable*> {
        public:
            using Base = TypeHandler<Backgroundable*>;
            BackgroundableHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
    };
}