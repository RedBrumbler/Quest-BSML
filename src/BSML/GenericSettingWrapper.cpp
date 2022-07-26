#include "BSML/GenericSettingWrapper.hpp"

DEFINE_TYPE(BSML, GenericSettingWrapper);

void BSML::GenericSettingWrapper::ctor() {
    applyOnChange = true;
    valueInfo = nullptr;
    setterInfo = nullptr;
    getterInfo = nullptr;
    onChangeInfo = nullptr;
}