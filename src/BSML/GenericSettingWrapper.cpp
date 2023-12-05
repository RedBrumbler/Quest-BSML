#include "BSML/GenericSettingWrapper.hpp"

DEFINE_TYPE(BSML, GenericSettingWrapper);

void BSML::GenericSettingWrapper::ctor() {
    applyOnChange = false;
    valueInfo = nullptr;
    setterInfo = nullptr;
    getterInfo = nullptr;
    onChangeInfo = nullptr;
}

bs_hook::Il2CppWrapperType BSML::GenericSettingWrapper::get_onChangeHost() {
    return onChangeHost ? onChangeHost : host;
}

bs_hook::Il2CppWrapperType BSML::GenericSettingWrapper::get_host() {
    return host ? host : onChangeHost;
}
