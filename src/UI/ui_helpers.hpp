#ifndef UI_HELPERS_HPP
#define UI_HELPERS_HPP

#include <imgui/imgui.h>


namespace ui_helpers
{
    inline void RenderSelectable(const char * str, int& index, int index_value);
    inline bool IconBtn(const char* icon, const ImVec2 size, float y_adjust);
}
#endif