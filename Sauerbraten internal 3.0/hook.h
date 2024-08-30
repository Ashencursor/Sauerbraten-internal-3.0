#pragma once
#include "pch.h"
#include "minhook/MinHook.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_opengl3_loader.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl2.h"


namespace Hook
{
	// Variables
	const inline auto Opengl = GetModuleHandle(L"opengl32.dll");
	inline const auto swapBuffersPtr =
		reinterpret_cast<uintptr_t>(GetProcAddress(Opengl, "wglSwapBuffers"));

	inline bool UnInject = false;


	// Functions for hooking
	void hook();
	void unHook();
	BOOL WINAPI DetourwglSwapBuffers(HDC hdc);
}