#include "../pch.h"
#include "hook.h"


void Hook::init() {
    //Init Wndproc for handling inputs from window
    Hook::oWndProc = (WNDPROC)SetWindowLongPtr(FindWindow(nullptr, L"Cube 2: Sauerbraten"), GWLP_WNDPROC, (LONG_PTR)Hook::hkWndProc);
    hook();
}

