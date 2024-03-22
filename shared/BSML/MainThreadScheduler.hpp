#pragma once

#include "custom-types/shared/macros.hpp"

#include "UnityEngine/MonoBehaviour.hpp"
#include <queue>

DECLARE_CLASS_CODEGEN(BSML, MainThreadScheduler, UnityEngine::MonoBehaviour,
    private:
        static std::queue<std::function<void()>> scheduledMethods;
        static std::mutex scheduledMethodsMutex;
        static std::queue<std::function<void()>> nextFrameScheduledMethods;
        static std::mutex nextFrameScheduledMethodsMutex;

    public:
        /// @brief schedule a method to be called on the main thread, or if you are on the main thread right now immediately
        static void Schedule(std::function<void()> method);

        template<typename T, typename U>
        static void Schedule(T instance, void (U::*method)()) {
            Schedule(std::bind(method, instance));
        }

        /// @brief schedule a method to be called the next frame
        static void ScheduleNextFrame(std::function<void()> method);

        template<typename T, typename U>
        static void ScheduleNextFrame(T instance, void (U::*method)()) {
            ScheduleNextFrame(std::bind(method, instance));
        }

        /// @brief method that checks whether the thread it's called from is the main thread
        static bool CurrentThreadIsMainThread();

    DECLARE_INSTANCE_METHOD(void, Update);
)
