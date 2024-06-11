#include "App.h"

#include <chrono>
#include <iostream>
#include <thread>

#include "core/clock.h"
#include "core/events/KeyboardEvent.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

const char *glsl_version = "#version 130";

App::App(Tracer::TracerStatusCode *status)
    : m_status(status), m_grid(Tracer::ui::Grid(16, 4, 3)), m_cursorPos({0, 0, 0}), dispatcher() {}

App::~App() {}

void App::render() {
    m_grid.render(m_cursorPos, gridState);
}

void App::init() {
    m_settings = Tracer::config::Settings();
    m_grid = Tracer::ui::Grid(m_settings.getSteps(), m_settings.getTracks(), m_settings.getSubTracks());
    m_input = Tracer::utils::Input();

    // Registering callbacks with the dispatcher
    dispatcher.registerCallback(GLFW_KEY_LEFT, [this](int key, int scancode, int action, int mods) { HandleKeyInput(key, scancode, action, mods); });
    dispatcher.registerCallback(GLFW_KEY_RIGHT, [this](int key, int scancode, int action, int mods) { HandleKeyInput(key, scancode, action, mods); });
    dispatcher.registerCallback(GLFW_KEY_UP, [this](int key, int scancode, int action, int mods) { HandleKeyInput(key, scancode, action, mods); });
    dispatcher.registerCallback(GLFW_KEY_DOWN, [this](int key, int scancode, int action, int mods) { HandleKeyInput(key, scancode, action, mods); });
    dispatcher.registerCallback(GLFW_KEY_ENTER, [this](int key, int scancode, int action, int mods) { HandleUtilKeyPress(key, scancode, action, mods); });
}

void App::HandleUtilKeyPress(int key, int scancode, int action, int mods) {
    std::cout << "Key pressed: " << key << "," << scancode << ", " << mods << std::endl;
    if (key == GLFW_KEY_ENTER) {
        if (action == GLFW_PRESS) {
            m_grid.toggleCell(gridState, m_cursorPos.row, m_cursorPos.col);
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
    if (m_grid.cellToggled(gridState)) {
        const int maxSubCols = m_grid.getSubCols();
        const int newSubColPos = m_cursorPos.sub + colMove;

        if (newSubColPos >= maxSubCols) {
            m_cursorPos.sub = 0;
            const int newColPos = m_cursorPos.col + 1;
            if (newColPos >= m_grid.getCols()) {
                return;
            }
            m_cursorPos.col = newColPos;
            m_grid.toggleCell(gridState, m_cursorPos.row, m_cursorPos.col);
            return;
        }

        if (newSubColPos < 0) {
            m_cursorPos.sub = maxSubCols - 1;
            const int newColPos = m_cursorPos.col - 1;
            if (newColPos < 0) {
                return;
            }
            m_cursorPos.col = newColPos;
            m_grid.toggleCell(gridState, m_cursorPos.row, m_cursorPos.col);
            return;
        }

        m_cursorPos.sub = newSubColPos;

        const int newRowPos = m_cursorPos.row + rowMove;

        if (newRowPos >= m_grid.getRows()) {
            m_cursorPos.row = 0;
            m_grid.toggleCell(gridState, m_cursorPos.row, m_cursorPos.col);
            return;
        }

        if (newRowPos < 0) {
            m_cursorPos.row = m_grid.getRows() - 1;
            m_grid.toggleCell(gridState, m_cursorPos.row, m_cursorPos.col);
            return;
        }

        m_cursorPos.row = newRowPos;
        m_grid.toggleCell(gridState, m_cursorPos.row, m_cursorPos.col);
        return;
    }

    const int newColPos = m_cursorPos.col + colMove;
    const int newRowPos = m_cursorPos.row + rowMove;
    if (newColPos >= m_grid.getCols() || newColPos < 0) {
        return;
    }

    if (newRowPos >= m_grid.getRows()) {
        m_cursorPos.row = 0;
        return;
    }
    if (newRowPos < 0) {
        m_cursorPos.row = m_grid.getRows() - 1;
        return;
    }

    m_cursorPos.col = newColPos;
    m_cursorPos.row = newRowPos;
}

int App::run() {
    std::cout << "Starting Tracer...";
    init();
    GLFWwindow *window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "Glfw init fail";
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Glew init fail";
        return -1;
    }

    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, Tracer::events::KeyboardEvent::key_callback);

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImVec4 clear_color = ImColor(0x49, 0xA6, 0x95);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        int win_width, win_height;
        glfwGetWindowSize(window, &win_width, &win_height);
        ImGui::SetNextWindowSize(ImVec2(static_cast<float>(win_width), static_cast<float>(win_height)), ImGuiCond_Always);

        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::Begin("Fullscreen", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
        render();

        ImGui::End();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
};