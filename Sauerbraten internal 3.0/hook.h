#pragma once
#include "pch.h"
#include "minhook/MinHook.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_opengl3_loader.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl2.h"
#include "GUI/gui.h"


namespace Hook
{
	// Conditional for helping to uninject and release hooks
	inline bool UnInject = false;

	// Functions for hooking
	void hook();
	void unHook();




	//Detour for wglSwapBuffers
	BOOL WINAPI DetourwglSwapBuffers(HDC hdc);

	//Function pointer for the original wglswapbuffers function in game to store it in
	typedef BOOL(WINAPI* wglSwapBuffers_t)(HDC);
	inline wglSwapBuffers_t fpwglSwapBuffers = nullptr;

	// Pointers to functions
	const inline auto Opengl = GetModuleHandle(L"opengl32.dll");
	inline const auto swapBuffersPtr =
		reinterpret_cast<uintptr_t>(GetProcAddress(Opengl, "wglSwapBuffers"));
	
	//Detour for SetRelativeMouseMode
	typedef int(*SDL_SetRelativeMouseMode_t)(int);
	inline auto SDL_RelativeMouseModePtr = reinterpret_cast<SDL_SetRelativeMouseMode_t>(GetProcAddress(GetModuleHandle(L"SDL2.dll"), "SDL_SetRelativeMouseMode"));


	// Detour for WNDPROC 
	LRESULT WINAPI hkWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	// For WNDPROC hook to store original one
	inline WNDPROC oWndProc;

}