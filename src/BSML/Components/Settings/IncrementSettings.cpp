#include "BSML/Components/Settings/IncrementSetting.hpp"
#include <limits>
#include <fmt/core.h>

DEFINE_TYPE(BSML, IncrementSetting);

namespace BSML {
    void IncrementSetting::ctor() {
        this->construct();
        minValue = -std::numeric_limits<float>::infinity();
        maxValue = std::numeric_limits<float>::infinity();
        increments = 1.0f;
        isInt = false;
        currentValue = 0.0f;
        digits = 2;
    }

    void IncrementSetting::Setup() {
        UpdateState();
    }

    void IncrementSetting::IncButtonPressed() {
        currentValue += increments;
        EitherPressed();
    }

    void IncrementSetting::DecButtonPressed() {
        currentValue -= increments;
        EitherPressed();
    }

    void IncrementSetting::EitherPressed() {
        UpdateState();
    }

    void IncrementSetting::ValidateRange() {
        if (currentValue < minValue)
            currentValue = minValue;
        else if (currentValue > maxValue)
            currentValue = maxValue;
    }

    void IncrementSetting::UpdateState() {
        ValidateRange();

        set_enableDec(currentValue > minValue);
        set_enableInc(currentValue < maxValue);
        set_text(TextForValue(currentValue));
    }

    StringW IncrementSetting::TextForValue(float value) {
        // since the formatter can't differentiate between int and float, we just call it
        if (formatter) return formatter(value);

        if (isInt) {
            return fmt::format("{}", ConvertToInt(value));
        } else {
            return fmt::format("{:.{}f}", value, digits);
        }
    }

    int IncrementSetting::ConvertToInt(float value) {
        if (value < -std::numeric_limits<int>::infinity()) {
            return -std::numeric_limits<int>::infinity();
        }
        if (value > std::numeric_limits<int>::infinity()) {
            return std::numeric_limits<int>::infinity();
        }
        else return value;
    }


}