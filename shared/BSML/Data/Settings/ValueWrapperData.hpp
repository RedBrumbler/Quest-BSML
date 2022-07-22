#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "ValueWrapper.hpp"

namespace BSML {
    class ValueWrapperData {
        public:
            ValueWrapperData() {};
            explicit ValueWrapperData(const tinyxml2::XMLElement& elem);
            
            auto get_fieldName() const { return fieldName; }
            auto get_onChange() const { return onChange; }
            auto get_propertyName() const { return propertyName; }
            auto get_startValue() const { return startValue; }
            
            void Apply(BSML::ValueWrapper* wrapper, Il2CppObject* host) const;
        private:
            std::string fieldName;
            std::string onChange;

            std::string propertyName;
            bool startValue = false;
    };
}