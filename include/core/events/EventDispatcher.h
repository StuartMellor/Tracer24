#ifndef TRACER_EVENTDISPATCHER_H
#define TRACER_EVENTDISPATCHER_H

#include <functional>
#include <unordered_map>
#include <vector>

namespace Tracer {
namespace events {

class EventDispatcher {
   public:
    using EventCallback = std::function<void(int key, int scancode, int action, int mods)>;

    void registerCallback(int eventType, EventCallback callback) {
        callbacks[eventType].push_back(callback);
    }

    void dispatch(int eventType, int key, int scancode, int action, int mods) {
        for (const auto& callback : callbacks[eventType]) {
            callback(key, scancode, action, mods);
        }
    }

   private:
    std::unordered_map<int, std::vector<EventCallback>> callbacks;
};

}  // namespace events
}  // namespace Tracer

#endif  // TRACER_EVENTDISPATCHER_H
