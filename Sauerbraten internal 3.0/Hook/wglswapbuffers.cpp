#include "../pch.h"
#include "hook.h"
#include "../GUI/gui.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

BOOL WINAPI Hook::DetourwglSwapBuffers(HDC hdc)//__stdcall
{
    // Initialize ImGui ONLY ONCE
    // This initialization MUST be done in the detour function or it will NOT WORK
    if (!GUI::init) {
        std::cout << "Intialized\n";
        GUI::initialize();
        GUI::init = true;
    }

    std::cout << "hooked\n";
    if (GUI::isActive) {
        if (GUI::hwnd)
        {
            std::cout << "NewFrame\n";
            // Start the ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            // Example ImGui window
            GUI::Render();

            // Rendering
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
    }
    // Destroy ImGui in the Detour function as it was Created here
    if (Hook::UnInject) {
        std::cout << "Destorying\n";
        //Cleanup imgui
        GUI::destroy();
    }
    // Call the original wglSwapBuffers function
    return fpwglSwapBuffers(hdc);
}