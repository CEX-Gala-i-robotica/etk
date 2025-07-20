#ifndef ENTRY_H
#define ENTRY_H




#define DEFAULT_UI_FONT "assets/fonts/Parkinsans-SemiBold.ttf"

//#define ICON_WIDTH 25
//#define ICON_HEIGHT 25






// This was implemented back when I used GTK3 (loading the GTK CSS Theme and the svg icons)
void load_assets();
void ui_init(); // Initializes the required rendering backed for nuklear (xcb_cairo for now. In the future: adding backed support for raw framebuffer)
void ui_main(int ac, char *av[]); // The main entry point of GUI

#endif