#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "BSML/Components/Settings/SliderSetting.hpp"

namespace BSML {
    class SliderSettingData {
        public:
            SliderSettingData() {};
            explicit SliderSettingData(const tinyxml2::XMLElement& elem);
            
            auto get_increment() const { return increment; }
            auto get_min() const { return min; }
            auto get_max() const { return max; }
            auto get_isInt() const { return isInt; }
            auto get_digits() const { return digits; }

            void Apply(BSML::SliderSetting* sliderSetting) const;
        private:
            std::optional<float> increment;
            std::optional<float> min;
            std::optional<float> max;
            std::optional<bool> isInt;
            std::optional<int> digits;
    };
}