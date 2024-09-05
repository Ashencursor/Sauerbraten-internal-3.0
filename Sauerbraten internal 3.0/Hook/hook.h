#pragma once
#include "../pch.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/imgui_impl_opengl3_loader.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_opengl2.h"

#include "../minhook/MinHook.h"


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

namespace Hook
{
	// Conditional for helping to uninject and release hooks
	inline bool UnInject = false;

	//Detour for wglSwapBuffers
	BOOL WINAPI DetourwglSwapBuffers(HDC hdc);

	//Function pointer for the original wglswapbuffers function in game to store it in
	typedef BOOL(WINAPI* wglSwapBuffers_t)(HDC);
	inline wglSwapBuffers_t fpwglSwapBuffers = nullptr;

	// Pointers to functions
	inline const auto Opengl = GetModuleHandle(L"opengl32.dll");
	inline const auto swapBuffersPtr =
		reinterpret_cast<uintptr_t>(GetProcAddress(Opengl, "wglSwapBuffers"));
	
	//Detour for SetRelativeMouseMode
	typedef int(*SDL_SetRelativeMouseMode_t)(int);
	inline auto DetourSDL_RelativeMouseMode = reinterpret_cast<SDL_SetRelativeMouseMode_t>(GetProcAddress(GetModuleHandle(L"SDL2.dll"), "SDL_SetRelativeMouseMode"));


	// Detour for WNDPROC 
	LRESULT WINAPI hkWndProc(HWND hWnd, UINT umsg, WPARAM wParam, LPARAM lParam);
	// For WNDPROC hook to store original one
	inline WNDPROC oWndProc = nullptr;

	// Functions for hooking
	inline void hook()
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

	inline void unHook()
	{
		std::cout << "UnHooking\n";
		// Disable the hook
		MH_DisableHook(reinterpret_cast<LPVOID>(MH_ALL_HOOKS));
		// Uninitialize MinHook
		MH_Uninitialize();
	}
	void init();
}
