#include "BSML/Parsing/BSMLStringValue.hpp"

namespace BSML {
    void BSMLStringValue::SetValue(Il2CppObject* val) {
        if (val) {
            static auto stringKlass = classof(StringW);
            if (val->klass == stringKlass) {
                value = static_cast<std::string>(StringW(val));
            } else {
                value = static_cast<std::string>(val->ToString());
            }
        }
    }

    Il2CppObject* BSMLStringValue::GetValue() {
        return StringW(value);
    }
}