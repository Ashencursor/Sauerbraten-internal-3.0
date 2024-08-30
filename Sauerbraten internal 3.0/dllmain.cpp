#include "pch.h"
#include "hook.h"
#include "GUI/gui.h"


// Original function that will be hooked
__declspec(noinline) void MyFunction(const std::string& message) {
    std::cout << "My original Function: " << message << std::endl;
}


// Original function pointer for wglSwapBuffers
const inline auto Opengl = GetModuleHandle(L"opengl32.dll");
inline const auto swapBuffersPtr =
reinterpret_cast<uintptr_t>(GetProcAddress(Opengl, "wglSwapBuffers"));
typedef BOOL(WINAPI* wglSwapBuffers_t)(HDC);
wglSwapBuffers_t fpwglSwapBuffers = nullptr;

int WINAPI DetourwglSwapBuffers(HDC hdc)//__stdcall
{

    std::cout << "hooked\n";
    
    // Call the original wglSwapBuffers function
    return fpwglSwapBuffers(hdc);
}

void Hook()
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





void unHook()
{
    // Disable the hook
    MH_DisableHook(reinterpret_cast<LPVOID>(swapBuffersPtr));

    // Uninitialize MinHook
    MH_Uninitialize();
}



BOOL WINAPI Thread(HMODULE hModule) {
    // Attempt to send a message to the console
    AllocConsole(); // Allocate a console for this process
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout); // Redirect stdout to the console

    Hook();

    while (true) {

        if (GetAsyncKeyState(VK_DELETE) & 1) {
            return 0;
        }
    }
    unHook();
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

