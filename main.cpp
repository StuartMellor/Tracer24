// #include "imgui.h"
// #include "imgui_impl_glfw.h"
// #include "imgui_impl_opengl3.h"
// #include <GL/glew.h>
// #include <GLFW/glfw3.h>
// #include <iostream>
// // include imgui table
// #include "imgui_internal.h"

// const char *glsl_version = "#version 130";
// int main(void) {
//   GLFWwindow *window;

//   /* Initialize the library */
//   if (!glfwInit())
//     return -1;

//   /* Create a windowed mode window and its OpenGL context */
//   window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//   if (!window) {
//     glfwTerminate();
//     return -1;
//   }

//   /* Make the window's context current */
//   glfwMakeContextCurrent(window);

//   if (glewInit() != GLEW_OK)
//     std::cerr << "Glew init fail";

//   ImGui::CreateContext();
//   ImGui::StyleColorsDark();
//   ImGui_ImplGlfw_InitForOpenGL(window, true);
//   ImGui_ImplOpenGL3_Init(glsl_version);

//   ImVec4 clear_color = ImColor(0x49, 0xA6, 0x95);
//   /* Loop until the user closes the window */

//   while (!glfwWindowShouldClose(window)) {
//     glfwPollEvents();

//     ImGui_ImplOpenGL3_NewFrame();
//     ImGui_ImplGlfw_NewFrame();
//     ImGui::NewFrame();

//     // Begin a fullscreen ImGui window
//     int win_width, win_height;
//     glfwGetWindowSize(window, &win_width, &win_height);
//     ImGui::SetNextWindowSize(ImVec2(win_width, win_height), ImGuiCond_Always);

//     ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
//     ImGui::Begin("Fullscreen", NULL,
//                  ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
//                      ImGuiWindowFlags_NoMove |
//                      ImGuiWindowFlags_NoBringToFrontOnFocus);

//     // Create a Menu
//     if (ImGui::BeginMainMenuBar()) {
//       if (ImGui::BeginMenu("File")) {
//         if (ImGui::MenuItem("Open", "Ctrl+O")) {
//           // Handle File Open
//         }
//         if (ImGui::MenuItem("Save", "Ctrl+S")) {
//           // Handle File Save
//         }
//         ImGui::EndMenu();
//       }
//       ImGui::EndMainMenuBar();
//     }

//     // Create 3 x 24 cols and rows of cells which are a box with three blocks
//     // of two blocks of text in, such that the format is -- -- -- and can be
//     // replaced with text such as A1 10 125 and render it in the centre of the
//     // screen with white text. Between each column, there should be a vertical
//     // line separating
//     ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), false,
//                       ImGuiWindowFlags_HorizontalScrollbar);
//     ImGui::Columns(24, NULL, false);
//     for (int i = 0; i < 24 * 3; i++) {
//       ImGui::Text("A1");
//       ImGui::NextColumn();
//       ImGui::Text("10");
//       ImGui::NextColumn();
//       ImGui::Text("125");
//       ImGui::NextColumn();
//     }
//     ImGui::EndChild();

//     ImGui::End(); // End of fullscreen window

//     ImGui::Render();
//     int display_w, display_h;
//     glfwGetFramebufferSize(window, &display_w, &display_h);
//     glViewport(0, 0, display_w, display_h);
//     glClear(GL_COLOR_BUFFER_BIT);
//     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

//     glfwSwapBuffers(window);
//   }

//   ImGui_ImplOpenGL3_Shutdown();
//   ImGui_ImplGlfw_Shutdown();
//   ImGui::DestroyContext();

//   glfwDestroyWindow(window);
//   glfwTerminate();
//   return 0;
// }