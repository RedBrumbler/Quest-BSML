#pragma once

#include "BSML/TypeHandlers/TypeHandler.hpp"
#include "BSML/Components/Backgroundable.hpp"

namespace BSML {
    class BackgroundableHandler : public TypeHandler<Backgroundable*> {
        public:
            BackgroundableHandler() : TypeHandler<Backgroundable*>() {}
            using T = Backgroundable*;
            using Base = TypeHandler<Backgroundable*>;

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
    };
}