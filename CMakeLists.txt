cmake_minimum_required(VERSION 3.1)

project(Boilerplate)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Collect project source files dynamically
file(GLOB_RECURSE PROJECT_SRC
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/include/*.h
)

add_executable(Tracer
    ${PROJECT_SRC}
    ${PROJECT_SOURCE_DIR}/Tracer.cpp
)

# Set C++ standard
set_property(TARGET Tracer PROPERTY CXX_STANDARD 23)

# Compiler options
if(MSVC)
    target_compile_options(Tracer PRIVATE /W4) # Enable all warnings
else()
    target_compile_options(Tracer PRIVATE -Wall -Wextra -pedantic)
endif()

# Add GLFW
add_subdirectory(${PROJECT_SOURCE_DIR}/glfw EXCLUDE_FROM_ALL)
target_link_libraries(Tracer PRIVATE glfw)

# Add GLEW
add_definitions(-DGLEW_STATIC)
add_subdirectory(${PROJECT_SOURCE_DIR}/glew EXCLUDE_FROM_ALL)
target_link_libraries(Tracer PRIVATE libglew_static)

# Add GLM
add_subdirectory(${PROJECT_SOURCE_DIR}/glm EXCLUDE_FROM_ALL)
target_link_libraries(Tracer PRIVATE glm)

# Include directories
target_include_directories(Tracer PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

# Platform-specific settings
if(WIN32)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Tracer)
endif()
