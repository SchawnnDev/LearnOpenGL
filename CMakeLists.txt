cmake_minimum_required(VERSION 3.19)
project(LearnOpenGL)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(LearnOpenGL_SRCS src/main.cpp src/glad.c)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/glfw)

link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(LearnOpenGL ${LearnOpenGL_SRCS})
target_link_libraries(LearnOpenGL ${OPENGL_LIBRARIES} glfw)

target_include_directories(LearnOpenGL PUBLIC include ${OPENGL_INCLUDE_DIRS})