#pragma once

#include "TypeHandler.hpp"
#include "../Components/PageButton.hpp"

namespace BSML {
    class PageButtonHandler : public TypeHandler<BSML::PageButton> {
        public:
            using Base = TypeHandler<BSML::PageButton>;
            PageButtonHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
    };
}
