cmake_minimum_required(VERSION 3.1)

project(Boilerplate)

set(CMAKE_CXX_STANDARD 17)

# if(MSVC)
# add_compile_options(/Qspectre)
# endif()
add_executable(Tracer
    ${PROJECT_SOURCE_DIR}/Tracer.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imconfig.h
    ${PROJECT_SOURCE_DIR}/imgui/imgui_draw.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui_impl_glfw.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui_impl_glfw.h
    ${PROJECT_SOURCE_DIR}/imgui/imgui_impl_opengl3.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui_impl_opengl3.h
    ${PROJECT_SOURCE_DIR}/imgui/imgui_internal.h
    ${PROJECT_SOURCE_DIR}/imgui/imgui_widgets.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui.h
    ${PROJECT_SOURCE_DIR}/imgui/imstb_rectpack.h
    ${PROJECT_SOURCE_DIR}/imgui/imstb_textedit.h
    src/App.cpp
    src/core/ui/Cell.cpp
    src/core/ui/Col.cpp
    src/core/ui/Grid.cpp
)

set_property(TARGET Tracer PROPERTY CXX_STANDARD 11)
target_compile_options(Tracer PRIVATE -Wall)

add_subdirectory(${PROJECT_SOURCE_DIR}/glfw EXCLUDE_FROM_ALL)
target_link_libraries(Tracer PRIVATE glfw)

add_definitions(-DGLEW_STATIC)
add_subdirectory(${PROJECT_SOURCE_DIR}/glew EXCLUDE_FROM_ALL)
target_link_libraries(Tracer PRIVATE libglew_static)

add_subdirectory(${PROJECT_SOURCE_DIR}/glm EXCLUDE_FROM_ALL)
target_link_libraries(Tracer PRIVATE glm)

target_include_directories(Tracer PRIVATE
    ${PROJECT_SOURCE_DIR}/imgui
    include
)

IF(WIN32)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Tracer)
ENDIF()
