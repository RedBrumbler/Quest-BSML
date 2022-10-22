#pragma once

#include "TypeHandler.hpp"
#include "../Components/CustomListTableData.hpp"

namespace BSML {
    class CustomListTableDataHandler : public TypeHandler<BSML::CustomListTableData*> {
        public:
            using Base = TypeHandler<BSML::CustomListTableData*>;
            CustomListTableDataHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
            virtual void HandleType(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) override;
    };
}