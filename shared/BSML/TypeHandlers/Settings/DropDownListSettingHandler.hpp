#pragma once

#include "BSML/TypeHandlers/TypeHandler.hpp"
#include "BSML/Components/Settings/DropdownListSetting.hpp"

namespace BSML {
    class DropdownListSettingHandler : public TypeHandler<BSML::DropdownListSetting*> {
        public:
            using Base = TypeHandler<BSML::DropdownListSetting*>;
            DropdownListSettingHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;

            virtual void HandleType(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) override;
    };
}