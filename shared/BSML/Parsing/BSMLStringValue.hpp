#pragma once

#include "BSMLValue.hpp"

namespace BSML {
    struct BSMLStringValue : public BSMLValue {
        std::string value;

        void SetValue(System::Object* val) override;
        System::Object* GetValue() override;
    };
}
