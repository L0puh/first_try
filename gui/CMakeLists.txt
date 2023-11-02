cmake_minimum_required(VERSION 3.0)

project(my_app)

find_package(OpenGL REQUIRED)

link_directories(libs/glfw)
include_directories(libs/imgui)
include_directories(libs/glfw)
# include_directories(include)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(my_app ${SOURCES})

target_link_libraries(my_app PRIVATE ${OPENGL_gl_LIBRARY})
target_link_libraries(my_app PRIVATE glfw)

# file(COPY resources DESTINATION /)
