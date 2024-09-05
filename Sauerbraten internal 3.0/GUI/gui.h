#pragma once
#include "../pch.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_opengl2.h"
#include "../imgui/imgui_impl_opengl3.h"


namespace GUI {

	inline HWND hwnd = FindWindow(nullptr, L"Cube 2: Sauerbraten");
	inline bool isActive = false;
	inline bool init = false;

	void Render();
	void initialize();
	void destroy();
}