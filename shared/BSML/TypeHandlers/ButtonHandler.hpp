#pragma once

#include "BSML/TypeHandlers/TypeHandler.hpp"
#include "UnityEngine/UI/Button.hpp"

namespace BSML {
    class ButtonHandler : public TypeHandler<UnityEngine::UI::Button*> {
        public:
            using Base = TypeHandler<UnityEngine::UI::Button*>;
            ButtonHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
            virtual void HandleType(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) override;
    };
}