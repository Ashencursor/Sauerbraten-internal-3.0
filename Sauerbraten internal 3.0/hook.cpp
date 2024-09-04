#include "pch.h"
#include "hook.h"
#include "minhook/MinHook.h"
#include "GUI/gui.h"
#include <Windows.h>



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

    void Hook::hook()
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

    void Hook::unHook()
    {
        std::cout << "UnHooking\n";
        // Disable the hook
        MH_DisableHook(reinterpret_cast<LPVOID>(MH_ALL_HOOKS));
        // Uninitialize MinHook
        MH_Uninitialize();
    }

    LRESULT WINAPI Hook::hkWndProc(HWND hWnd, UINT umsg, WPARAM wParam, LPARAM lParam) {

        // Must be up here to correctly process events
        if (GUI::isActive) {
            //This will allow things to interact with the imgui menu, so if my cursor from tabbing out of the game closes the menu then it closes
            if (ImGui_ImplWin32_WndProcHandler(hWnd, umsg, wParam, lParam))
                return true;
        }

        if (GUI::isActive) {

            // Ensure the cursor is visible
            ShowCursor(TRUE);
            //ImGui::GetIO().MouseDrawCursor = true;// Use to draw mouse
            Hook::SDL_RelativeMouseModePtr(0);// Set Mouse free from center of the screen

            // Handle mouse input differently or ignore it for the game
            // Can stop the in game mouse from moving
            if (umsg == WM_MOUSEMOVE || umsg == WM_LBUTTONDOWN || umsg == WM_RBUTTONDOWN) {
                // Let ImGui handle the mouse input instead of the game
                return 0; // Return 0 to stop the game from handling the input
            }
        }
        else {
            // Hide the cursor when the menu is closed
            //ShowCursor(FALSE);
            //ImGui::GetIO().MouseDrawCursor = false;
        }

        // Call OriginalWndProc
        return CallWindowProcW(oWndProc, hWnd, umsg, wParam, lParam);
    }



