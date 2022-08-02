#pragma once

#include "BSML/Parsing/BSMLValue.hpp"

namespace BSML {
    struct BSMLStringValue : public BSMLValue {
        std::string value;

        void SetValue(Il2CppObject* val) override;
        Il2CppObject* GetValue() override;
    };
}