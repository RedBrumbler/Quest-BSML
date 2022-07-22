#include "ValueWrapper.hpp"

DEFINE_TYPE(BSML, ValueWrapper);

namespace BSML {
    SetterType ValueWrapper::get_setterType() const {
        return static_cast<SetterType>(setterType);
    }

    void ValueWrapper::set_setterType(int value) {
        this->setterType = value;
    }

    void ValueWrapper::set_setterType(SetterType value) {
        this->setterType = static_cast<int>(value);
    }

    int operator& (BSML::SetterType lhs, BSML::SetterType rhs) {
        return static_cast<int>(lhs) & static_cast<int>(rhs);
    }
    
    BSML::SetterType operator| (BSML::SetterType lhs, BSML::SetterType rhs) {
        return static_cast<BSML::SetterType>(static_cast<int>(lhs) | static_cast<int>(rhs));
    }

    BSML::SetterType& operator|= (BSML::SetterType& self, BSML::SetterType rhs) {
        self = self | rhs;
        return self;
    }
}