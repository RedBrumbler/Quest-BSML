#include "BSML/Components/Settings/BaseSetting.hpp"

DEFINE_TYPE(BSML, BaseSetting);

namespace BSML {
    void BaseSetting::base_ctor() {
        genericSetting = GenericSettingWrapper::New_ctor();
    }
}