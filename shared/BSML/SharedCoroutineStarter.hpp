#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

// equivalent to shared coroutine starter
DECLARE_CLASS_CODEGEN(BSML, SharedCoroutineStarter, UnityEngine::MonoBehaviour,
    private:
        static SafePtrUnity<UnityEngine::MonoBehaviour> instance;
    public:
        static UnityEngine::MonoBehaviour* get_instance();
)
