#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <unordered_map>
#include <vector>

class EventManager {
public:
    using EventCallback = std::function<void()>;

    void waitForEvent() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] { return eventTriggered; });
        std::cout << "Event received!\n";
        callRegisteredEvent();
    }

    void setEventTriggered() {
        std::lock_guard<std::mutex> lock(mutex_);
        eventTriggered = true;
        cv_.notify_one();
    }

    void registerEventCallback(EventCallback callback, int triggerId) {
        eventCallbacks_[triggerId] = std::move(callback);
    }

private:
    void callRegisteredEvent() {
        auto triggerId = std::this_thread::get_id();  // Get the ID of the triggering thread
        auto it = eventCallbacks_.find(triggerId);
        if (it != eventCallbacks_.end()) {
            it->second();
        }
    }

    std::mutex mutex_;
    std::condition_variable cv_;
    bool eventTriggered = false;
    std::unordered_map<std::thread::id, EventCallback> eventCallbacks_;
};

class EventTrigger {
public:
    EventTrigger(EventManager& manager, int triggerId) : eventManager(manager), triggerId(triggerId) {}

    void operator()() {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Simulate some work before triggering event
        eventManager.setEventTriggered();
    }

    void registerEventCallback(EventManager::EventCallback callback) {
        eventManager.registerEventCallback(std::move(callback), triggerId);
    }

private:
    EventManager& eventManager;
    int triggerId;
};

int main() {
    EventManager eventManager;

    std::thread eventListener(&EventManager::waitForEvent, &eventManager);

    // Create three threads using EventTrigger to trigger the event
    EventTrigger eventTrigger1(eventManager, 1);
    EventTrigger eventTrigger2(eventManager, 2);
    EventTrigger eventTrigger3(eventManager, 3);

    // Register specific events for each trigger
    eventTrigger1.registerEventCallback([] { std::cout << "EventTrigger1 callback!\n"; });
    eventTrigger2.registerEventCallback([] { std::cout << "EventTrigger2 callback!\n"; });
    eventTrigger3.registerEventCallback([] { std::cout << "EventTrigger3 callback!\n"; });

    std::thread thread1(std::ref(eventTrigger1));
    std::thread thread2(std::ref(eventTrigger2));
    std::thread thread3(std::ref(eventTrigger3));

    eventListener.join();
    thread1.join();
    thread2.join();
    thread3.join();

    return 0;
}