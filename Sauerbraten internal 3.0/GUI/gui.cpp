#include "../pch.h"

#include "gui.h"

void GUI::Render()
{
    std::cout << "Rendering\n";

    ImGui::Begin("Sauerbraten Internal Hack");
    ImGui::SetWindowSize(ImVec2(600, 400));
    ImGui::Text("This is a hooked ImGui window.");

    if (ImGui::BeginTabBar("MyTabBar"))
    {
        if (ImGui::BeginTabItem("Aimbot"))
        {
            ImGui::Text("Aimbot");
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("ESP"))
        {
            ImGui::Text("ESP");

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Random"))
        {
            ImGui::Text("Random");
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
    ImGui::End();
}

//Things to init for the menu
void GUI::initialize()
{
    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup ImGui style
    ImGui::StyleColorsDark();
    if (!hwnd) {
        std::cout << "hwnd incorrect\n";
    }
    // Initialize ImGui OpenGL and Win32
    ImGui_ImplWin32_Init(GUI::hwnd); 
    ImGui_ImplOpenGL3_Init(); // Specify your OpenGL version

}

void GUI::destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

