#include "gui.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_opengl2.h"
#include "../imgui/imgui_impl_opengl3.h"

void GUI::Render()
{
    ImGui::Begin("Sauerbraten Internal Hack");
    ImGui::SetWindowSize(ImVec2(400, 600));
    ImGui::Text("This is a hooked ImGui window.");
    ImGui::End();
}

void GUI::init()
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
    ImGui_ImplOpenGL2_Init(); // Specify your OpenGL version

}

void GUI::destroy()
{
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}
