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

    AppData app = {0};

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "ToolPalette Selection Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *palette = gtk_tool_palette_new();

    // First group
    GtkWidget *group1 = gtk_tool_item_group_new("Group 1");
    gtk_container_add(GTK_CONTAINER(palette), group1);

    for (int i = 1; i <= 3; ++i) {
        gchar *label = g_strdup_printf("Item %d", i);
        GtkToggleToolButton *item = GTK_TOGGLE_TOOL_BUTTON(gtk_toggle_tool_button_new());
        gtk_tool_button_set_label(GTK_TOOL_BUTTON(item), label);
        gtk_tool_item_group_insert(GTK_TOOL_ITEM_GROUP(group1), GTK_TOOL_ITEM(item), -1);
        g_signal_connect(item, "toggled", G_CALLBACK(on_tool_item_toggled), &app);
        g_free(label);
    }

    // Second group
    GtkWidget *group2 = gtk_tool_item_group_new("Group 2");
    gtk_container_add(GTK_CONTAINER(palette), group2);

    for (int i = 1; i <= 2; ++i) {
        gchar *label = g_strdup_printf("Tool %d", i);
        GtkToggleToolButton *item = GTK_TOGGLE_TOOL_BUTTON(gtk_toggle_tool_button_new());
        gtk_tool_button_set_label(GTK_TOOL_BUTTON(item), label);
        gtk_tool_item_group_insert(GTK_TOOL_ITEM_GROUP(group2), GTK_TOOL_ITEM(item), -1);
        g_signal_connect(item, "toggled", G_CALLBACK(on_tool_item_toggled), &app);
        g_free(label);
    }

    GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrolled), palette);

    gtk_container_add(GTK_CONTAINER(window), scrolled);

    gtk_widget_show_all(window);
    gtk_main();
}