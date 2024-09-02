#pragma once
#include "../pch.h"
#include "../hook.h"

namespace GUI {
	void Render();

	inline HWND hwnd = FindWindow(nullptr, L"Cube 2: Sauerbraten");
	inline bool isActive = false;
	inline bool init = false;
	void initialize();
	void destroy();
}