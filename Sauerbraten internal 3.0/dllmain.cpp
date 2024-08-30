#include "pch.h"
#include "hook.h"
#include "GUI/gui.h"





namespace Hook {
    //Function pointer for the original wglswapbuffers function in game to store it in
    typedef BOOL(WINAPI* wglSwapBuffers_t)(HDC);
    wglSwapBuffers_t fpwglSwapBuffers = nullptr;

    BOOL WINAPI DetourwglSwapBuffers(HDC hdc)//__stdcall
    {
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
        if (MH_EnableHook(reinterpret_cast<LPVOID>(Hook::swapBuffersPtr)) != MH_OK)
        {
            return;
        }


    }

    void unHook()
    {
        std::cout << "UnHooking\n";
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

