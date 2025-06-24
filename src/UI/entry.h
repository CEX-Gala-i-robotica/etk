#ifndef ENTRY_H
#define ENTRY_H

#include <gtk/gtk.h>






#define ICON_WIDTH 25
#define ICON_HEIGHT 25

extern GtkWidget *button1, *button2, *button3, *button4, *button5, *button6;
extern GtkWidget *main_window;
extern GtkWidget *settings_icon;





void load_assets();
void ui_entry(int ac, char *av[]);
#endif