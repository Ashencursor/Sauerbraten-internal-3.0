#include "gui.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_opengl2.h"
#include "../imgui/imgui_impl_opengl3.h"

void GUI::Render()
{
    std::cout << "Rendering\n";

    ImGui::Begin("Sauerbraten Internal Hack");
    ImGui::SetWindowSize(ImVec2(600, 400));
    ImGui::Text("This is a hooked ImGui window.");
    ImGui::End();


}

//Things to init for the menu
void GUI::initialize()
{
    //Init Wndproc for handling inputs from window
    Hook::oWndProc = (WNDPROC)SetWindowLongPtr(FindWindow(nullptr, L"Cube 2: Sauerbraten"), GWLP_WNDPROC, (LONG_PTR)Hook::hkWndProc);
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
