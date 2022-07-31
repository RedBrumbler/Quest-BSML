#pragma once

#include "BSML/TypeHandlers/TypeHandler.hpp"
#include "BSML/Components/Settings/SliderSetting.hpp"

namespace BSML {
    class SliderSettingHandler : public TypeHandler<BSML::SliderSetting*> {
        public:
            using Base = TypeHandler<BSML::SliderSetting*>;
            SliderSettingHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
    };
}