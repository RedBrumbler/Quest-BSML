#include "BSML/GenericSettingWrapper.hpp"

DEFINE_TYPE(BSML, GenericSettingWrapper);

void BSML::GenericSettingWrapper::ctor() {
    applyOnChange = true;
    valueInfo = nullptr;
    setterInfo = nullptr;
    getterInfo = nullptr;
    onChangeInfo = nullptr;
}

Il2CppObject* BSML::GenericSettingWrapper::get_onChangeHost() {
    return onChangeHost ? onChangeHost : host;
}

Il2CppObject* BSML::GenericSettingWrapper::get_host() {
    return host ? host : onChangeHost;
}

