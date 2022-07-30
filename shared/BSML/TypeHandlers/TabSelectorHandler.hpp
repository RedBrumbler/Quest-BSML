#pragma once

#include "BSML/TypeHandlers/TypeHandler.hpp"
#include "BSML/Components/TabSelector.hpp"

namespace BSML {
    class TabSelectorHandler : public TypeHandler<BSML::TabSelector*> {
        public:
            using Base = TypeHandler<BSML::TabSelector*>;
            TabSelectorHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
            virtual void HandleTypeAfterParse(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) override;
    };
}