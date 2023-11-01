cmake_minimum_required(VERSION 3.6)
project(app)

set(CMAKE_CXX_STANDARD 11)
set(APP app)

add_subdirectory(imgui)
include_directories(${PROJECT_SOURCE_DIR})

add_executable(${APP} main.cpp)
target_link_libraries(${APP} imgui)

# glfw
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

target_link_libraries(
        ${APP}
        glfw
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${EXTRA_LIBS}
)
