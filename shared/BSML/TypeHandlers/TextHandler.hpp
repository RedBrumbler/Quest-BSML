#pragma once

#include "BSML/TypeHandlers/TypeHandler.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

namespace BSML {
    class TextHandler : public TypeHandler<TMPro::TextMeshProUGUI*> {
        public:
            TextHandler() : TypeHandler<TMPro::TextMeshProUGUI*>() {}
            using T = TMPro::TextMeshProUGUI*;
            using Base = TypeHandler<TMPro::TextMeshProUGUI*>;

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
    };
}