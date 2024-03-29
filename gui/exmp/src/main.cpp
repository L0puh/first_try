#include <stdio.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


int main(int argc, char** argv) {
    if (!glfwInit()) 
        return 1;
    
    GLFWwindow* window = glfwCreateWindow(300, 300, "test window", NULL, NULL);
    glfwMakeContextCurrent(window);


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGuiWindowFlags flags = 0;
    flags |= ImGuiWindowFlags_NoBackground;
    flags |= ImGuiWindowFlags_NoDecoration;
    flags |= ImGuiWindowFlags_NoMove;
    flags |= ImGuiWindowFlags_AlwaysAutoResize;

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        // popup menu
        ImGui::NewFrame();
        {
            ImGui::Begin("menu", 0, flags);
            if(ImGui::Button("close")){
                return 0;
            } 

            if(ImGui::Button("menu")){
                ImGui::OpenPopup("menu");
            }
            if (ImGui::BeginPopup("menu", ImGuiWindowFlags_AlwaysAutoResize)){
                if(ImGui::BeginMenu("menu")){
                    if(ImGui::MenuItem("close", "Alt+F4")){return 0;};
                    static bool target = false;
                    ImGui::MenuItem("item", nullptr, &target);
                    ImGui::Checkbox("check", &target);
                    ImGui::EndMenu();
                }
                ImGui::EndPopup();
            }
             
            ImGui::End();
        }
        ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f,
                             io.DisplaySize.y * 0.5f),
                             ImGuiCond_Always, ImVec2(0.5f,0.5f));
        {
            ImGui::Begin("window", 0,  flags);
            if(ImGui::Button("button")) {
                ImGui::OpenPopup("button");
            }
            if( ImGui::BeginPopup("button", ImGuiWindowFlags_AlwaysAutoResize)) {
                    float window_width = ImGui::GetWindowWidth();
                    float window_height = ImGui::GetWindowHeight();
                    ImGui::Text("popuh example text!!");
                    if (ImGui::Button("ok"))
                        ImGui::CloseCurrentPopup();
                    ImGui::EndPopup();
            }
            ImGui::End();
        }
        ImGui::Render();

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
