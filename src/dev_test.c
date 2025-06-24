#include <gtk/gtk.h>






#include "dev_test.h"








typedef struct {
    GtkToggleToolButton *selected;
} AppData;

static void
on_tool_item_toggled(GtkToggleToolButton *button, gpointer user_data)
{
    AppData *app = user_data;
    if (gtk_toggle_tool_button_get_active(button)) {
        if (app->selected && app->selected != button)
            gtk_toggle_tool_button_set_active(app->selected, FALSE);
        app->selected = button;
        const gchar *label = gtk_tool_button_get_label(GTK_TOOL_BUTTON(button));
        g_print("Selected: %s\n", label ? label : "(no label)");
    } else if (app->selected == button) {
        app->selected = NULL;
    }
}




void Dev_Test(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Icon Button Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 100);

    GtkWidget *button = gtk_button_new();
    GtkWidget *image = gtk_image_new_from_icon_name("document-open", GTK_ICON_SIZE_BUTTON);
    gtk_button_set_image(GTK_BUTTON(button), image);

    gtk_container_add(GTK_CONTAINER(window), button);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();
}