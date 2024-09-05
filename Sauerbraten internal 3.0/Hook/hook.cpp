#include "../pch.h"
#include "../minhook/MinHook.h"

#include "hook.h"

/*

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
*/