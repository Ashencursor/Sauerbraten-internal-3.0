#include "pch.h"
#include "hook.h"
#include "GUI/gui.h"






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
}



BOOL WINAPI Thread(HMODULE hModule) {
    // Attempt to send a message to the console
    AllocConsole(); // Allocate a console for this process
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout); // Redirect stdout to the console

    //Init GUI
    GUI::init();
    GUI::hwnd = FindWindow(nullptr, L"Cube 2: Sauerbraten");

    Hook::hook();
  
    while (true) {


        if (GetAsyncKeyState(VK_INSERT) & 1) {
            GUI::isActive = !GUI::isActive;
        }


        if (GetAsyncKeyState(VK_DELETE) & 1) {
            return 0;
        }
    }
    //UnHook
    Hook::unHook();
    //Cleanup imgui
    GUI::destroy();

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

