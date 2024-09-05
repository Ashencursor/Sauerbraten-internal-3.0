#include "pch.h"
#include "Hook/hook.h"

#include "GUI/gui.h"


BOOL WINAPI Thread(HMODULE hModule) {
    // Attempt to send a message to the console
    AllocConsole(); // Allocate a console for this process
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout); // Redirect stdout to the console

    // Get game window handle
    GUI::hwnd = FindWindow(nullptr, L"Cube 2: Sauerbraten");
    Hook::init();
  
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

