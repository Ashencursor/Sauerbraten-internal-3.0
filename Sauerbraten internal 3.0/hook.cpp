#include "pch.h"
#include "hook.h"
#include "minhook/MinHook.h"
#include "GUI/gui.h"
#include <Windows.h>

/*

namespace Hook {
    typedef BOOL(WINAPI* wglSwapBuffers_t)(HDC);
    wglSwapBuffers_t fpwglSwapBuffers = nullptr;

    BOOL WINAPI DetourwglSwapBuffers(HDC hdc)//__stdcall
    {

        std::cout << "hooked\n";
        if (GUI::isActive) {
            if (GUI::hwnd)
            {
                std::cout << "Rendering\n";
                // Start the ImGui frame
                ImGui_ImplOpenGL2_NewFrame();
                ImGui_ImplWin32_NewFrame();
                ImGui::NewFrame();

                // Example ImGui window
                GUI::Render();

                // Rendering
                ImGui::Render();
                ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
            }
        }
        // Call the original wglSwapBuffers function
        return fpwglSwapBuffers(hdc);
    }

    void hook()
    {
        // Initialize MinHook
        if (MH_Initialize() != MH_OK)
        {
            return;
        }

        // Create a hook for wglSwapBuffers
        // Look at function declaration for more information on each argument
        if (MH_CreateHook(reinterpret_cast<LPVOID>(Hook::swapBuffersPtr), reinterpret_cast<LPVOID>(&DetourwglSwapBuffers), reinterpret_cast<LPVOID*>(&fpwglSwapBuffers)) != MH_OK)
        {
            return;
        }

        // Enable the hook
        if (MH_EnableHook(reinterpret_cast<LPVOID>(Hook::swapBuffersPtr)) != MH_OK)
        {
            return;
        }
    }

    void unHook()
    {
        // Disable the hook
        MH_DisableHook(reinterpret_cast<LPVOID>(Hook::swapBuffersPtr));

        // Uninitialize MinHook
        MH_Uninitialize();
    }
}*/