#pragma once

#include "BSML/TypeHandlers/TypeHandler.hpp"
#include "BSML/Components/ModalView.hpp"

namespace BSML {
    class ModalViewHandler : public TypeHandler<BSML::ModalView*> {
        public:
            using Base = TypeHandler<BSML::ModalView*>;
            ModalViewHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
    
            virtual void HandleType(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) override;
    };
}