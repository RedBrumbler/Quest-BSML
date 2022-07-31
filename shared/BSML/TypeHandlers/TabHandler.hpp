#pragma once

#include "BSML/TypeHandlers/TypeHandler.hpp"
#include "BSML/Components/Tab.hpp"

namespace BSML {
    class TabHandler : public TypeHandler<BSML::Tab*> {
        public:
            using Base = TypeHandler<BSML::Tab*>;
            TabHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
    };
}