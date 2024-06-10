#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <functional>

namespace Tracer {
namespace utils {
class Input {
   public:
    Input() = default;
    ~Input() = default;
    void listenForInput(GLFWwindow* window, std::function<void(int, int)> moveCursor, std::function<void(int)> handleUtilPress);

   private:
    void handleArrowKeys(GLFWwindow* window, std::function<void(int, int)> moveCursor);
    void handleUtilKeys(GLFWwindow* window, std::function<void(int)> handleUtilPress);
};
}  // namespace utils
}  // namespace Tracer