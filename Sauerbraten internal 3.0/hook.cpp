#include "pch.h"
#include "hook.h"
#include "minhook/MinHook.h"
#include "GUI/gui.h"
#include <Windows.h>



extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
/*
namespace Hook {

    BOOL WINAPI DetourwglSwapBuffers(HDC hdc)//__stdcall
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
        if (MH_EnableHook(reinterpret_cast<LPVOID>(MH_ALL_HOOKS)) != MH_OK)
        {
            return;
        }
        

    }

    void unHook()
    {
        std::cout << "UnHooking\n";
        // Disable the hook
        MH_DisableHook(reinterpret_cast<LPVOID>(MH_ALL_HOOKS));
        // Uninitialize MinHook
        MH_Uninitialize();
    }

    LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

        if (GUI::isActive) {
            switch (msg) {


            }
        }
        // Call OriginalWndProc
        return CallWindowProcW(oWndProc, hWnd, msg, wParam, lParam);
    }
}
*/


/*

    BOOL WINAPI DetourwglSwapBuffers(HDC hdc)//__stdcall
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
        if (MH_EnableHook(reinterpret_cast<LPVOID>(MH_ALL_HOOKS)) != MH_OK)
        {
            return;
        }


    }

    void unHook()
    {
        std::cout << "UnHooking\n";
        // Disable the hook
        MH_DisableHook(reinterpret_cast<LPVOID>(MH_ALL_HOOKS));
        // Uninitialize MinHook
        MH_Uninitialize();
    }
*/