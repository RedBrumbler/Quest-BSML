#include "BSML/MainThreadScheduler.hpp"
#include <mutex>

#include "UnityEngine/Time.hpp"

DEFINE_TYPE(BSML, MainThreadScheduler);

namespace BSML {
    std::queue<std::function<void()>> MainThreadScheduler::scheduledMethods;
    std::mutex MainThreadScheduler::scheduledMethodsMutex;
    std::queue<std::function<void()>> MainThreadScheduler::nextFrameScheduledMethods;
    std::mutex MainThreadScheduler::nextFrameScheduledMethodsMutex;
    std::vector<std::pair<float, std::function<void()>>> MainThreadScheduler::scheduledAfterTimeMethods;
    std::mutex MainThreadScheduler::scheduledAfterTimeMethodsMutex;

    bool MainThreadScheduler::CurrentThreadIsMainThread() {
        // unity icall for whether this is the main thread
        static auto currentThreadIsMainThread = il2cpp_utils::resolve_icall<bool>("UnityEngine.Object::CurrentThreadIsMainThread");
        return currentThreadIsMainThread();
    }

    void MainThreadScheduler::Schedule(std::function<void ()> method) {
        // if this thread is already main thread, just run the method
        if (CurrentThreadIsMainThread()) {
            method();
            return;
        }

        std::lock_guard<std::mutex> lock(scheduledMethodsMutex);
        scheduledMethods.push(method);
    }

    void MainThreadScheduler::ScheduleNextFrame(std::function<void()> method) {
        std::lock_guard<std::mutex> lock(nextFrameScheduledMethodsMutex);
        nextFrameScheduledMethods.push(method);
    }

    void MainThreadScheduler::ScheduleAfterTime(float time, std::function<void()> method) {
        std::lock_guard<std::mutex> lock(scheduledAfterTimeMethodsMutex);
        scheduledAfterTimeMethods.emplace_back(time, method);
        std::stable_sort(scheduledAfterTimeMethods.begin(), scheduledAfterTimeMethods.end(), [](auto const& a, auto const& b){ return a.first < b.first; });
    }

    void MainThreadScheduler::Update() {
        {
            // acquire lock
            std::lock_guard<std::mutex> scheduledMethodsLock(scheduledMethodsMutex);
            // run through our backlog
            while (!scheduledMethods.empty()) {
                scheduledMethods.front()();
                scheduledMethods.pop();
            }

            // aqcuire lock
            std::lock_guard<std::mutex> nextFrameMethodsLock(nextFrameScheduledMethodsMutex);
            // push all the nextframe methods onto the scheduled methods queue
            while(!nextFrameScheduledMethods.empty()) {
                scheduledMethods.push(nextFrameScheduledMethods.front());
                nextFrameScheduledMethods.pop();
            }
        }
        {
            // get delta time to use in decreasing timers
            auto delta = UnityEngine::Time::get_deltaTime();
            // aqcuire lock for time scheduled methods
            std::lock_guard<std::mutex> scheduledAfterTimeLock(scheduledAfterTimeMethodsMutex);
            // decrease all the timers
            for(auto& [time, func] : scheduledAfterTimeMethods) {
                time -= delta;
            }

            // if a timer hit below 0, we can invoke the method and remove it
            while(scheduledAfterTimeMethods.front().first <= 0.0f) {
                scheduledAfterTimeMethods.front().second();
                scheduledAfterTimeMethods.erase(scheduledAfterTimeMethods.begin());
            }
        }

        }
    }
}
