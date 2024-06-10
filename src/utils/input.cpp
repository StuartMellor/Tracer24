#include "utils/input.h"

#include <chrono>
#include <unordered_map>

void Tracer::utils::Input::listenForInput(GLFWwindow *window, std::function<void(int, int)> moveCursor, std::function<void(int)> handleUtilPress) {
    handleUtilKeys(window, handleUtilPress);
    handleArrowKeys(window, moveCursor);
};

void Tracer::utils::Input::handleUtilKeys(GLFWwindow *window, std::function<void(int)> handleUtilPress) {
    static std::unordered_map<int, bool> keyPressed = {
        {GLFW_KEY_ENTER, false},
        {GLFW_KEY_SPACE, false},
        {GLFW_KEY_BACKSPACE, false},
        {GLFW_KEY_DELETE, false}};

    for (auto &key : {GLFW_KEY_ENTER, GLFW_KEY_SPACE, GLFW_KEY_BACKSPACE, GLFW_KEY_DELETE}) {
        if (glfwGetKey(window, key) == GLFW_PRESS) {
            if (!keyPressed[key]) {
                handleUtilPress(key);
                keyPressed[key] = true;
            }
        } else {
            keyPressed[key] = false;
        }
    }
}

void Tracer::utils::Input::handleArrowKeys(GLFWwindow *window, std::function<void(int, int)> moveCursor) {
    static std::unordered_map<int, bool> keyPressed = {
        {GLFW_KEY_LEFT, false},
        {GLFW_KEY_RIGHT, false},
        {GLFW_KEY_UP, false},
        {GLFW_KEY_DOWN, false}};

    static std::unordered_map<int, std::chrono::steady_clock::time_point> lastPressTime = {
        {GLFW_KEY_LEFT, std::chrono::steady_clock::now()},
        {GLFW_KEY_RIGHT, std::chrono::steady_clock::now()},
        {GLFW_KEY_UP, std::chrono::steady_clock::now()},
        {GLFW_KEY_DOWN, std::chrono::steady_clock::now()}};

    static std::unordered_map<int, std::chrono::steady_clock::time_point> pressStartTime = {
        {GLFW_KEY_LEFT, std::chrono::steady_clock::now()},
        {GLFW_KEY_RIGHT, std::chrono::steady_clock::now()},
        {GLFW_KEY_UP, std::chrono::steady_clock::now()},
        {GLFW_KEY_DOWN, std::chrono::steady_clock::now()}};

    auto now = std::chrono::steady_clock::now();

    const std::chrono::milliseconds initialDelay(400);    // Initial delay before repeat starts
    const std::chrono::milliseconds fasterDelay(200);     // Faster delay after holding for a while
    const std::chrono::milliseconds fastestDelay(10);     // Fastest delay after holding even longer
    const std::chrono::milliseconds holdDuration1(700);   // Time threshold to switch to faster delay
    const std::chrono::milliseconds holdDuration2(1300);  // Time threshold to switch to fastest delay

    auto calculateDelay = [&](auto pressStartTime) {
        auto holdDuration = now - pressStartTime;
        if (holdDuration > holdDuration2) {
            return fastestDelay;
        } else if (holdDuration > holdDuration1) {
            return fasterDelay;
        } else {
            return initialDelay;
        }
    };

    for (auto &key : {GLFW_KEY_LEFT, GLFW_KEY_RIGHT, GLFW_KEY_UP, GLFW_KEY_DOWN}) {
        int deltaX = (key == GLFW_KEY_LEFT) ? -1 : (key == GLFW_KEY_RIGHT) ? 1
                                                                           : 0;
        int deltaY = (key == GLFW_KEY_UP) ? -1 : (key == GLFW_KEY_DOWN) ? 1
                                                                        : 0;

        if (glfwGetKey(window, key) == GLFW_PRESS) {
            if (!keyPressed[key]) {
                moveCursor(deltaX, deltaY);
                keyPressed[key] = true;
                lastPressTime[key] = now;
                pressStartTime[key] = now;
            } else if ((now - lastPressTime[key]) > calculateDelay(pressStartTime[key])) {
                moveCursor(deltaX, deltaY);
                lastPressTime[key] = now;
            }
        } else {
            keyPressed[key] = false;
        }
    }
}
