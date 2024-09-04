#include "pch.h"
#include "hook.h"
#include "GUI/gui.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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

    LRESULT WINAPI hkWndProc(HWND hWnd, UINT umsg, WPARAM wParam, LPARAM lParam) {

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

        switch (umsg) {

        }

        // Call OriginalWndProc
        return CallWindowProcW(oWndProc, hWnd, umsg, wParam, lParam);
    }
}

BOOL WINAPI Thread(HMODULE hModule) {
    // Attempt to send a message to the console
    AllocConsole(); // Allocate a console for this process
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout); // Redirect stdout to the console

    // Get game window handle
    GUI::hwnd = FindWindow(nullptr, L"Cube 2: Sauerbraten");

    Hook::hook();
  
    while (true) {


        if (GetAsyncKeyState(VK_INSERT) & 1) {
            GUI::isActive = !GUI::isActive;
        }

        if (GetAsyncKeyState(VK_DELETE) & 1) {
            break;
        }
    }
    //Once out of loop wglswapbuffers is still hooked so it'll call it and then destroy imgui set FinishedHook to true
    Hook::UnInject = true;

    //UnHook
    Hook::unHook();

    fclose(f);//what
    FreeConsole();//Detach thread from process
    FreeLibraryAndExitThread(hModule, 0);//Unloads dll from process and terminates the thread 

    return TRUE;
}





BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, reinterpret_cast<PTHREAD_START_ROUTINE>(Thread), hModule, 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

