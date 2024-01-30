#pragma once

#include "custom-types/shared/macros.hpp"

#include "UnityEngine/MonoBehaviour.hpp"
#include <queue>

DECLARE_CLASS_CODEGEN_EXPORT(BSML, MainThreadScheduler, UnityEngine::MonoBehaviour,
    private:
        static std::queue<std::function<void()>> scheduledMethods;
        static std::mutex scheduledMethodsMutex;

    public:
        /// @brief schedule a method to be called on the main thread, or if you are on the main thread right now immediately
        static void Schedule(std::function<void()> method);

        template<typename T, typename U>
        static void Schedule(T instance, void (U::*method)()) {
            Schedule(std::bind(method, instance));
        }

        /// @brief method that checks whether the thread it's called from is the main thread
        static bool CurrentThreadIsMainThread();

    DECLARE_INSTANCE_METHOD(void, Update);
)
