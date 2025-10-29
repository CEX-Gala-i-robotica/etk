#include <raylib.h>
#include <raymath.h>
#include <rlImGui.h>
#include <imgui.h>




#include "ui_helpers.hpp"


/* Handle single selection switching */
void ui_helpers::RenderSelectable(const char * str, int& index, int index_value)
{
    ImGui::PushID(index_value); // ImGui will warn me about the same values for the components lol (Good practice tbh)
    if(ImGui::Selectable(str, index == index_value))
        index = index_value;
    ImGui::PopID();
}