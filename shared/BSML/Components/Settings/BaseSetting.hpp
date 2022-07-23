#pragma once

#include "custom-types/shared/macros.hpp"
#include "BSML/GenericSettingWrapper.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

DECLARE_CLASS_CODEGEN(BSML, BaseSetting, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_FIELD(GenericSettingWrapper*, genericSetting);

    DECLARE_CTOR(base_ctor);
)