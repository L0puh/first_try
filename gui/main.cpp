#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

int main(int argc, char** argv) {
    // Initialize GLFW
    if (!glfwInit())
        return 1;

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui Example", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    // Initialize ImGui
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfwGL3_Init(window, true);
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        //todo
    }

    // Cleanup
    ImGui_ImplGlfwGL3_Shutdown();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
