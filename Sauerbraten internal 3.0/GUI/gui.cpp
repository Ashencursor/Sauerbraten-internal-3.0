#include "gui.h"
#include "../imgui/imgui.h"

void GUI::Render()
{
    ImGui::Begin("Hello, Sauerbraten!");
    ImGui::Text("This is a hooked ImGui window.");
    ImGui::End();
}
