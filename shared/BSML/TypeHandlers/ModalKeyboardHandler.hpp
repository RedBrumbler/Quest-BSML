#pragma once

#include "TypeHandler.hpp"
#include "../Components/Keyboard/ModalKeyboard.hpp"

namespace BSML {
    class ModalKeyboardHandler : public TypeHandler<BSML::ModalKeyboard> {
        public:
            using Base = TypeHandler<BSML::ModalKeyboard>;
            ModalKeyboardHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;

            virtual void HandleType(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) override;
            virtual void HandleTypeAfterParse(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) override;
    };
}
