#pragma once
#include "../pch.h"

namespace GUI {
	void Render();

	inline HWND hwnd = FindWindow(nullptr, L"Cube 2: Sauerbraten");
	inline bool isActive = false;
}