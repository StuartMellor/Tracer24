
#include "App.h"

#include <chrono>
#include <iostream>
#include <thread>

#include "core/clock.h"
#include "core/ui/Grid.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "utils/types.h"

const char *glsl_version = "#version 130";

App::~App(){};

// int App::run() {
//     // start clo
//     // Clock clockSystem(10, 4, 120.00);  // Assuming '4' as an arbitrary number of columns
//     // clockSystem.start();
//     // std::this_thread::sleep_for(std::chrono::seconds(10));
//     // *m_status = Tracer::TracerStatusCode::EXIT;

//     return 0;
// }

void App::render() {
    m_grid.render(m_cursorPos);
}

void App::init() {
    m_settings = Tracer::config::Settings();
    m_grid = Tracer::ui::Grid(m_settings.getSteps(), m_settings.getTracks());
    m_input = Tracer::utils::Input();
}

void App::moveCursor(int colMove, int rowMove) {
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
    };

    m_cursorPos.col = newColPos;
    m_cursorPos.row = newRowPos;
};

void App::HandleUtilKeyPress(int key, int action) {
    if (key == GLFW_KEY_ENTER) {
        if (action == GLFW_PRESS) {
            m_grid.toggleCell(m_cursorPos.col, m_cursorPos.row);
        }
    }
}

int App::run() {
    std::cout << "Starting Tracer...";
    init();
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "Glfw init fail";
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Glew init fail";
        return -1;
    }

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImVec4 clear_color = ImColor(0x49, 0xA6, 0x95);
    /* Loop until the user closes the window */

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Begin a fullscreen ImGui window
        int win_width, win_height;
        glfwGetWindowSize(window, &win_width, &win_height);
        ImGui::SetNextWindowSize(ImVec2(static_cast<float>(win_width), static_cast<float>(win_height)), ImGuiCond_Always);

        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::Begin("Fullscreen", NULL,
                     ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoMove |
                         ImGuiWindowFlags_NoBringToFrontOnFocus);
        m_input.listenForInput(window, [&](int x, int y) { moveCursor(x, y); }, [&](int key) { HandleUtilKeyPress(key, GLFW_PRESS); });
        render();

        ImGui::End();  // End of fullscreen window

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
}