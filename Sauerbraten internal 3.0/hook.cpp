#include "pch.h"
#include "hook.h"
#include "minhook/MinHook.h"
#include "GUI/gui.h"
#include <Windows.h>

/*

// Original function pointer for wglSwapBuffers
typedef BOOL(WINAPI* wglSwapBuffers_t)(HDC);
wglSwapBuffers_t fpwglSwapBuffers = nullptr;

void Hook::Hook()
{
    // Initialize MinHook
    if (MH_Initialize() != MH_OK)
    {
        return;
    }

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup ImGui style
    ImGui::StyleColorsDark();

    // Initialize ImGui OpenGL and Win32
    ImGui_ImplWin32_Init(GUI::hwnd); // Replace `hwnd` with the actual window handle
    ImGui_ImplOpenGL3_Init("#version 130"); // Specify your OpenGL version

    // Create a hook for wglSwapBuffers
    // Look at function declaration for more information on each argument
    if (MH_CreateHook(reinterpret_cast<LPVOID>(swapBuffersPtr), reinterpret_cast<LPVOID>(&DetourwglSwapBuffers), reinterpret_cast<LPVOID*>(&fpwglSwapBuffers)) != MH_OK)
    {
        return;
    }

    // Enable the hook
    if (MH_EnableHook(reinterpret_cast<LPVOID>(swapBuffersPtr)) != MH_OK)
    {
        return;
    }
}





void Hook::unHook()
{
    // Disable the hook
    MH_DisableHook(reinterpret_cast<LPVOID>(swapBuffersPtr));

    // Uninitialize MinHook
    MH_Uninitialize();
}

BOOL WINAPI Hook::DetourwglSwapBuffers(HDC hdc)//__stdcall
{

    if (GUI::hwnd)
    {
        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        // Example ImGui window
        GUI::Render();

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    // Call the original wglSwapBuffers function
    return fpwglSwapBuffers(hdc);
}
*/