#include "../pch.h"
#include "hook.h"
#include "../GUI/gui.h"

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
        Hook::DetourSDL_RelativeMouseMode(0);// Set Mouse free from center of the screen

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
