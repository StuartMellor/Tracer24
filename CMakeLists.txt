cmake_minimum_required(VERSION 3.1)

project(Boilerplate)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure VCPKG_ROOT is set correctly
if(DEFINED ENV{VCPKG_ROOT})
    # Convert backslashes to forward slashes
    string(REPLACE "\\" "/" VCPKG_ROOT $ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
    message(STATUS "Using vcpkg from ${VCPKG_ROOT}")
else()
    message(FATAL_ERROR "Please install vcpkg and set the VCPKG_ROOT environment variable to the vcpkg directory")
endif()

# Include the vcpkg toolchain file
include(${CMAKE_TOOLCHAIN_FILE})

# Collect project source files dynamically
file(GLOB_RECURSE PROJECT_SRC
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/include/*.h
)

add_executable(Tracer
    ${PROJECT_SRC}
    ${PROJECT_SOURCE_DIR}/Tracer.cpp
)

# Print a message to the command line
message(STATUS "Starting configuration for project Boilerplate")

# Set C++ standard
message(STATUS "Setting C++ standard to 23")
set_property(TARGET Tracer PROPERTY CXX_STANDARD 23)

# Compiler options
if(MSVC)
    message(STATUS "Using MSVC compiler")
    target_compile_options(Tracer PRIVATE /W4) # Enable all warnings
else()
    message(STATUS "Using non-MSVC compiler")
    target_compile_options(Tracer PRIVATE -Wall -Wextra -pedantic)
endif()

# Find packages using vcpkg
find_package(Freetype REQUIRED)
if(Freetype_FOUND)
    message(STATUS "Freetype found")
else()
    message(FATAL_ERROR "Freetype not found")
endif()

find_package(ZLIB REQUIRED)
if(ZLIB_FOUND)
    message(STATUS "Zlib found")
else()
    message(FATAL_ERROR "Zlib not found")
endif()

find_package(PNG REQUIRED)
if(PNG_FOUND)
    message(STATUS "LibPNG found")
else()
    message(FATAL_ERROR "LibPNG not found")
endif()

find_package(BZip2 REQUIRED)
if(BZip2_FOUND)
    message(STATUS "BZip2 found")
else()
    message(FATAL_ERROR "BZip2 not found")
endif()

# Manually locate Brotli library and include directories
find_path(BROTLI_INCLUDE_DIRS "brotli/decode.h" PATH_SUFFIXES "include" REQUIRED)
find_library(BROTLI_LIBRARIES "brotlidec" PATH_SUFFIXES "lib" REQUIRED)

if(BROTLI_INCLUDE_DIRS AND BROTLI_LIBRARIES)
    message(STATUS "Brotli found")
else()
    message(FATAL_ERROR "Brotli not found")
endif()

# Add GLFW
add_subdirectory(${PROJECT_SOURCE_DIR}/glfw EXCLUDE_FROM_ALL)
target_link_libraries(Tracer PRIVATE glfw)
message(STATUS "GLFW added")

# Add GLEW
add_definitions(-DGLEW_STATIC)
add_subdirectory(${PROJECT_SOURCE_DIR}/glew EXCLUDE_FROM_ALL)
target_link_libraries(Tracer PRIVATE libglew_static)
message(STATUS "GLEW added")

# Add GLM
add_subdirectory(${PROJECT_SOURCE_DIR}/glm EXCLUDE_FROM_ALL)
target_link_libraries(Tracer PRIVATE glm)
message(STATUS "GLM added")

# Link libraries found by vcpkg
target_link_libraries(Tracer PRIVATE freetype ${ZLIB_LIBRARIES} ${PNG_LIBRARIES} ${BZIP2_LIBRARIES} ${BROTLI_LIBRARIES})

# Include directories
target_include_directories(Tracer PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/freeglut/include
    ${FREETYPE_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIRS}
    ${PNG_INCLUDE_DIRS}
    ${BZIP2_INCLUDE_DIRS}
    ${BROTLI_INCLUDE_DIRS}
)

# Platform-specific settings
if(WIN32)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Tracer)
    message(STATUS "Setting VS startup project to Tracer")
endif()

message(STATUS "Configuration complete")
