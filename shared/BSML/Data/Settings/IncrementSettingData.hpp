#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "BSML/Components/Settings/IncrementSetting.hpp"

namespace BSML {
    class IncrementSettingData {
        public:
            IncrementSettingData() {};
            explicit IncrementSettingData(const tinyxml2::XMLElement& elem);
            
            auto get_increment() const { return increment; }
            auto get_min() const { return min; }
            auto get_max() const { return max; }
            auto get_isInt() const { return isInt; }

            void Apply(BSML::IncrementSetting* incrementSetting) const;
        private:
            std::optional<float> increment;
            std::optional<float> min;
            std::optional<float> max;
            std::optional<bool> isInt;
    };
}