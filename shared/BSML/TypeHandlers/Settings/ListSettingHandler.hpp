#pragma once

#include "../TypeHandler.hpp"
#include "../../Components/Settings/ListSetting.hpp"

namespace BSML {
    class ListSettingHandler : public TypeHandler<BSML::ListSetting> {
        public:
            using Base = TypeHandler<BSML::ListSetting>;
            ListSettingHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;

            virtual void HandleType(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) override;
    };
}
