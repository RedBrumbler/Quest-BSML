#pragma once

#pragma once

#include "BSML/TypeHandlers/TypeHandler.hpp"
#include "BSML/Components/Settings/IncrementSetting.hpp"

namespace BSML {
    class IncrementSettingHandler : public TypeHandler<BSML::IncrementSetting*> {
        public:
            using Base = TypeHandler<BSML::IncrementSetting*>;
            IncrementSettingHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
    };
}