#pragma once

#include "BSMLValue.hpp"

namespace BSML {
    struct BSMLStringValue : public BSMLValue {
        std::string value;

        void SetValue(bs_hook::Il2CppWrapperType val) override;
        bs_hook::Il2CppWrapperType GetValue() override;
    };
}
