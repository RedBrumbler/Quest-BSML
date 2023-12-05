#include "BSML/Parsing/BSMLStringValue.hpp"

namespace BSML {
    void BSMLStringValue::SetValue(bs_hook::Il2CppWrapperType val) {
        if (val) {
            static auto stringKlass = classof(StringW);
            if (static_cast<Il2CppObject*>(val)->klass == stringKlass) {
                value = static_cast<std::string>(StringW(val));
            } else {
                value = static_cast<std::string>(System::Object(val.convert()).ToString());
            }
        }
    }

    bs_hook::Il2CppWrapperType BSMLStringValue::GetValue() {
        return StringW(value);
    }
}
