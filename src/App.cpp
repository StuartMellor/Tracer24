#include "App.h"

#include <chrono>
#include <iostream>
#include <thread>

#include "core/clock.h"
#include "core/events/KeyboardEvent.h"

const char *glsl_version = "#version 130";

void checkGLError(const char *stmt, const char *fname, int line) {
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "OpenGL error " << err << ", at " << stmt << " in " << fname << " on line " << line << std::endl;
        exit(1);
    }
}

#define GL_CHECK(stmt)                           \
    do {                                         \
        stmt;                                    \
        checkGLError(#stmt, __FILE__, __LINE__); \
    } while (0)

void App::init(int windowWidth, int windowHeight) {
    m_settings = Tracer::config::Settings();
    Tracer::TracerData tracerData = Tracer::TracerData();

    m_grid = Tracer::ui::Grid(tracerData, windowWidth);
    m_input = Tracer::utils::Input();

    // Registering callbacks with the dispatcher
    dispatcher.registerCallback(GLFW_KEY_LEFT, [this](int key, int scancode, int action, int mods) { HandleKeyInput(key, scancode, action, mods); });
    dispatcher.registerCallback(GLFW_KEY_RIGHT, [this](int key, int scancode, int action, int mods) { HandleKeyInput(key, scancode, action, mods); });
    dispatcher.registerCallback(GLFW_KEY_UP, [this](int key, int scancode, int action, int mods) { HandleKeyInput(key, scancode, action, mods); });
    dispatcher.registerCallback(GLFW_KEY_DOWN, [this](int key, int scancode, int action, int mods) { HandleKeyInput(key, scancode, action, mods); });
    dispatcher.registerCallback(GLFW_KEY_ENTER, [this](int key, int scancode, int action, int mods) { HandleUtilKeyPress(key, scancode, action, mods); });
    dispatcher.registerCallback(GLFW_KEY_ESCAPE, [this](int key, int scancode, int action, int mods) { HandleUtilKeyPress(key, scancode, action, mods); });
}

void App::HandleUtilKeyPress(int key, int /*scancode*/, int action, int /*mods*/) {
    if (key == GLFW_KEY_ENTER) {
        if (action == GLFW_PRESS) {
            // Reset to first block within cell:
            m_cursorPos.sub = 0;
            m_grid.toggleCell(gridState, m_cursorPos.row, m_cursorPos.col);
        }
    }
    if (key == GLFW_KEY_ESCAPE) {
        if (action == GLFW_PRESS) {
            // Exit the application
            *m_status = Tracer::TracerStatusCode::EXIT;
        }
    }
    if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT) {
        if (action == GLFW_PRESS) {
            std::cout << "Shift pressed" << std::endl;
            shiftPressed = true;
        }
        if (action == GLFW_RELEASE) {
            std::cout << "Shift released" << std::endl;
            shiftPressed = false;
        }
    }
}

void App::HandleKeyInput(int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT || key == GLFW_KEY_UP || key == GLFW_KEY_DOWN) {
        if (action == GLFW_PRESS || action == GLFW_REPEAT) {
            int colMove = 0;
            int rowMove = 0;
            if (key == GLFW_KEY_LEFT) colMove = -1;
            if (key == GLFW_KEY_RIGHT) colMove = 1;
            if (key == GLFW_KEY_UP) rowMove = -1;
            if (key == GLFW_KEY_DOWN) rowMove = 1;
            moveCursor(colMove, rowMove);
        }
    } else {
        HandleUtilKeyPress(key, scancode, action, mods);
    }
}

void App::moveCursor(int colMove, int rowMove) {
    bool cellChanged = false;

    if (m_grid.cellToggled(gridState)) {
        const int maxSubCols = m_grid.getSubCols();
        const int newSubColPos = m_cursorPos.sub + colMove;

        if (newSubColPos >= maxSubCols) {
            m_cursorPos.sub = 0;
            const int newColPos = m_cursorPos.col + 1;
            if (newColPos < m_grid.getCols()) {
                m_cursorPos.col = newColPos;
                cellChanged = true;
            }
        } else if (newSubColPos < 0) {
            m_cursorPos.sub = maxSubCols - 1;
            const int newColPos = m_cursorPos.col - 1;
            if (newColPos >= 0) {
                m_cursorPos.col = newColPos;
                cellChanged = true;
            }
        } else {
            m_cursorPos.sub = newSubColPos;
        }

        const int newRowPos = m_cursorPos.row + rowMove;

        if (newRowPos >= m_grid.getRows()) {
            m_cursorPos.row = 0;
            cellChanged = true;
        } else if (newRowPos < 0) {
            m_cursorPos.row = m_grid.getRows() - 1;
            cellChanged = true;
        } else if (newRowPos != m_cursorPos.row) {
            m_cursorPos.row = newRowPos;
            cellChanged = true;
        }

        // Only toggle the cell if the row or column actually changed
        if (cellChanged) {
            m_grid.toggleCell(gridState, m_cursorPos.row, m_cursorPos.col);
        }
    } else {
        const int newColPos = m_cursorPos.col + colMove;
        const int newRowPos = m_cursorPos.row + rowMove;

        if (newColPos >= 0 && newColPos < m_grid.getCols()) {
            m_cursorPos.col = newColPos;
        }

        if (newRowPos >= 0 && newRowPos < m_grid.getRows()) {
            m_cursorPos.row = newRowPos;
        }
    }
}

void App::render() {
    // Clear the screen with a background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);                // Black background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear both color and depth buffer

    // Set up the viewport
    int display_w, display_h;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    // Set up the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, display_w, display_h, 0, -1, 1);  // Y axis goes down
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Render the grid (which includes the boxes)
    m_grid.render(m_cursorPos, gridState);

    // Swap buffers to display the rendered frame
    glfwSwapBuffers(glfwGetCurrentContext());
}

int App::run() {
    GLFWwindow *window;

    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed" << std::endl;
        return -1;
    }

    // Get the primary monitor
    GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(primaryMonitor);

    // Create a window with the desired width and height
    window = glfwCreateWindow(mode->width, mode->height, "Hello World", nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        std::cerr << "GLFW window creation failed" << std::endl;
        return -1;
    }

    // Maximize the window
    glfwMaximizeWindow(window);
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW initialization failed" << std::endl;
        return -1;
    }

    // Enable V-Sync
    glfwSwapInterval(1);

    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, Tracer::events::KeyboardEvent::key_callback);

    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

    init(windowWidth, windowHeight);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        render();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
