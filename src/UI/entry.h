#ifndef ENTRY_H
#define ENTRY_H

#include <gtk/gtk.h>






#define ICON_WIDTH 25
#define ICON_HEIGHT 25

extern GtkWidget *main_window;





void load_assets();
void ui_entry(int ac, char *av[]);
static void app_cleanup(GtkWidget *widget, gpointer data);
#endif