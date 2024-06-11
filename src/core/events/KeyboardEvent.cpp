#include "core/events/KeyboardEvent.h"

#include <App.h>

#include <iostream>

namespace Tracer {
namespace events {

KeyboardEvent::KeyboardEvent(EventDispatcher& dispatcher) : dispatcher(dispatcher) {
    std::cout << "KeyboardEvent constructor" << std::endl;
}

KeyboardEvent::~KeyboardEvent() {
    std::cout << "KeyboardEvent destructor" << std::endl;
}

void KeyboardEvent::handleEvent() {
    // Default implementation, can be overridden
}

void KeyboardEvent::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    if (app) {
        app->getDispatcher().dispatch(key, key, scancode, action, mods);
    }

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if ((key >= GLFW_KEY_0 && key <= GLFW_KEY_9) || (key >= GLFW_KEY_KP_0 && key <= GLFW_KEY_KP_9)) {
            std::cout << "Numerical key pressed: " << key << std::endl;
        } else if ((key >= GLFW_KEY_A && key <= GLFW_KEY_Z)) {
            std::cout << "Letter key pressed: " << key << std::endl;
        } else if (key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT || key == GLFW_KEY_UP || key == GLFW_KEY_DOWN) {
            // std::cout << "Arrow key pressed: " << key << std::endl;
        } else if (key == GLFW_KEY_LEFT_ALT || key == GLFW_KEY_RIGHT_ALT ||
                   key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_RIGHT_CONTROL ||
                   key == GLFW_KEY_ENTER || key == GLFW_KEY_ESCAPE ||
                   key == GLFW_KEY_TAB || key == GLFW_KEY_BACKSPACE ||
                   key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT) {
            std::cout << "Special key pressed: " << key << std::endl;
        } else {
            std::cout << "Other key pressed: " << key << std::endl;
        }
    }
}

}  // namespace events
}  // namespace Tracer
