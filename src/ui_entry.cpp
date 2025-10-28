#include <log_c/log.h>

#include <raylib.h>
#include <raymath.h>
#include <imgui.h>
#include <rlImGui.h>


#include "ui_entry.hpp"



// DPI scaling functions
float ScaleToDPIF(float value)
{
    return GetWindowScaleDPI().x * value;
}

int ScaleToDPII(int value)
{
    return int(GetWindowScaleDPI().x * value);
}

etk::AppEntry::AppEntry(void)
{
    // - - - - GUI - - - -

    //SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);

    log_info("Showing main window...");
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "ETK");
	SetTargetFPS(144);
	rlImGuiSetup(true);

    while(!WindowShouldClose())    // Detect window close button or ESC key
	{
        BeginDrawing();
		ClearBackground(DARKGRAY);

        rlImGuiBegin();

#ifdef ETK_PLATFORM_DRM && ETK_DEV
        ImGui::GetIO().MouseDrawCursor = true;
#endif

        bool open = true;
		ImGui::ShowDemoWindow(&open);

		open = true;
		if (ImGui::Begin("Test Window", &open))
		{
			ImGui::TextUnformatted(ICON_FA_JEDI);
		}
		ImGui::End();

		// end ImGui Content
		rlImGuiEnd();

        EndDrawing();
    }
}

etk::AppEntry::~AppEntry(void)
{
    rlImGuiShutdown();
    CloseWindow();
    log_info("App Exit");
}
