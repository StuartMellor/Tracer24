#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "core/events/BaseEvent.h"
#include "core/events/EventDispatcher.h"

namespace Tracer {
namespace events {

class KeyboardEvent : public BaseEvent {
   public:
    KeyboardEvent(EventDispatcher& dispatcher);
    ~KeyboardEvent();

    void handleEvent() override;
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

   private:
    EventDispatcher& dispatcher;
};

}  // namespace events
}  // namespace Tracer
