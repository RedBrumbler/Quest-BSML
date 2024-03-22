#include "BSML/MainThreadScheduler.hpp"
#include <mutex>

DEFINE_TYPE(BSML, MainThreadScheduler);

namespace BSML {
    std::queue<std::function<void()>> MainThreadScheduler::scheduledMethods;
    std::mutex MainThreadScheduler::scheduledMethodsMutex;
    std::queue<std::function<void()>> MainThreadScheduler::nextFrameScheduledMethods;
    std::mutex MainThreadScheduler::nextFrameScheduledMethodsMutex;

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

    void MainThreadScheduler::Update() {
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
}
