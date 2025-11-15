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

bool ui_helpers::IconBtn(const char* icon, const ImVec2 size = ImVec2(40, 40), float y_adjust = 0.0f)
{
    //float icon_height = ImGui::GetFontSize();
    //float offset_y = (size.y - icon_height) * 0.5f;
    //ImVec2 cursor = ImGui::GetCursorPos();
    //ImGui::SetCursorPosY(cursor.y + offset_y);
    //bool clicked;
    //ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 0));
    //clicked = ImGui::Button(icon, size);
    //ImGui::PopStyleVar();
    //ImGui::SetCursorPosY(cursor.y + size.y);
    //return clicked;

        ImGui::PushID(icon);
    // Reserve the area & handle clicks/hover/active
    ImGui::InvisibleButton("##icon_btn", size);
    bool clicked = ImGui::IsItemClicked();
    bool hovered = ImGui::IsItemHovered();
    bool active  = ImGui::IsItemActive();

    // Rect in screen coordinates
    ImVec2 rect_min = ImGui::GetItemRectMin();
    ImVec2 rect_max = ImGui::GetItemRectMax();

    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImGuiStyle& style = ImGui::GetStyle();

    // Background (uses ImGui button colors to match style)
    ImU32 bg_col = ImGui::GetColorU32(ImGuiCol_Button);
    ImU32 hover_col = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
    ImU32 active_col = ImGui::GetColorU32(ImGuiCol_ButtonActive);
    ImU32 use_col = active ? active_col : (hovered ? hover_col : bg_col);
    dl->AddRectFilled(rect_min, rect_max, use_col, style.FrameRounding);

    // Optional border
    dl->AddRect(rect_min, rect_max, ImGui::GetColorU32(ImGuiCol_Border), style.FrameRounding);

    // Compute text (icon glyph) size
    ImVec2 text_size = ImGui::CalcTextSize(icon, NULL, false);

    // Center text inside button rect. y_adjust lets you fix fonts with odd baselines.
    float text_x = rect_min.x + (size.x - text_size.x) * 0.5f;
    float text_y = rect_min.y + (size.y - text_size.y) * 0.5f + y_adjust;

    // Draw icon text using current font and size
    dl->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(text_x, text_y),
                ImGui::GetColorU32(ImGuiCol_Text), icon);

    ImGui::PopID();
    return clicked;
}
