#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include <string>

DECLARE_CLASS_CORDL(BSML, HotReloadFileWatcher, UnityEngine::MonoBehaviour,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(bs_hook::Il2CppWrapperType, host);
        DECLARE_INSTANCE_FIELD(bool, runCheck);
        DECLARE_INSTANCE_FIELD(int, lastFileEdit);
        DECLARE_INSTANCE_FIELD(int, fileHash);
        DECLARE_INSTANCE_FIELD(float, timeSinceLastCheck);
        DECLARE_INSTANCE_FIELD(float, checkInterval);

        public:
            std::string filePath;
    );

    FIELD_ACCESSOR(host);
    FIELD_ACCESSOR(runCheck);
    FIELD_ACCESSOR(lastFileEdit);
    FIELD_ACCESSOR(fileHash);
    FIELD_ACCESSOR(timeSinceLastCheck);
    FIELD_ACCESSOR(checkInterval);
    FIELD_ACCESSOR(filePath);

    DECLARE_INSTANCE_METHOD(void, Update);
    DECLARE_INSTANCE_METHOD(void, Reload);

    DECLARE_CTOR(ctor);
)
