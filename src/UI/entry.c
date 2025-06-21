#include <gtk/gtk.h>






#include "entry.h"
#include "theme.h"











GtkWidget *main_window;

/*
Internal functions
*/


void load_css_theme()
{
    GtkCssProvider *css_provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    
    
    gtk_css_provider_load_from_data(css_provider, css_theme, -1, NULL);
    
    gtk_style_context_add_provider_for_screen(
        screen,
        GTK_STYLE_PROVIDER(css_provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
    
    g_object_unref(css_provider);
}


// Button click handlers
void on_button_clicked(GtkWidget *button, gpointer data)
{
    const char *label = gtk_button_get_label(GTK_BUTTON(button));
    g_print("Button clicked: %s\n", label);
}

void on_toggle_style(GtkWidget *button, gpointer data)
{
    GtkWidget *target_button = GTK_WIDGET(data);
    GtkStyleContext *context = gtk_widget_get_style_context(target_button);
    
    if (gtk_style_context_has_class(context, "btn-primary")) {
        gtk_style_context_remove_class(context, "btn-primary");
        gtk_style_context_add_class(context, "btn-danger");
        gtk_button_set_label(GTK_BUTTON(target_button), "Danger Button");
    } else {
        gtk_style_context_remove_class(context, "btn-danger");
        gtk_style_context_add_class(context, "btn-primary");
        gtk_button_set_label(GTK_BUTTON(target_button), "Primary Button");
    }
}



void ui_structure()
{
    GtkWidget *button1, *button2, *button3, *button4, *button5, *button6;
    GtkWidget *vbox;
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(main_window), vbox);
    
    // Create buttons
    button1 = gtk_button_new_with_label("Default Button");
    g_signal_connect(button1, "clicked", G_CALLBACK(on_button_clicked), NULL);
    
    button2 = gtk_button_new_with_label("Primary Button");
    gtk_style_context_add_class(gtk_widget_get_style_context(button2), "btn-primary");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_button_clicked), NULL);
    
    button3 = gtk_button_new_with_label("Success Button");
    gtk_style_context_add_class(gtk_widget_get_style_context(button3), "btn-success");
    g_signal_connect(button3, "clicked", G_CALLBACK(on_button_clicked), NULL);
    
    button4 = gtk_button_new_with_label("Danger Button");
    gtk_style_context_add_class(gtk_widget_get_style_context(button4), "btn-danger");
    g_signal_connect(button4, "clicked", G_CALLBACK(on_button_clicked), NULL);
    
    button5 = gtk_button_new_with_label("Rounded Button");
    GtkStyleContext *context5 = gtk_widget_get_style_context(button5);
    gtk_style_context_add_class(context5, "btn-primary");
    gtk_style_context_add_class(context5, "btn-rounded");
    g_signal_connect(button5, "clicked", G_CALLBACK(on_button_clicked), NULL);
    
    button6 = gtk_button_new_with_label("Large Button");
    GtkStyleContext *context6 = gtk_widget_get_style_context(button6);
    gtk_style_context_add_class(context6, "btn-success");
    gtk_style_context_add_class(context6, "btn-large");
    g_signal_connect(button6, "clicked", G_CALLBACK(on_button_clicked), NULL);
    
    // Toggle button to demonstrate dynamic styling
    GtkWidget *toggle_button = gtk_button_new_with_label("Toggle Style");
    g_signal_connect(toggle_button, "clicked", G_CALLBACK(on_toggle_style), button2);
    
    // Add buttons to box
    gtk_box_pack_start(GTK_BOX(vbox), button1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button3, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button4, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button5, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button6, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), toggle_button, FALSE, FALSE, 0);
}


void ui_entry(int ac, char *av[])
{
    gtk_init(&ac, &av);
    
    
    main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(main_window), "MPP Box");
    gtk_window_set_default_size(GTK_WINDOW(main_window), 500, 500);
    gtk_container_set_border_width(GTK_CONTAINER(main_window), 20);
    
    load_css_theme();
    
    
    ui_structure();
    
    
    // Connect window destroy signal
    g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Show all widgets
    gtk_widget_show_all(main_window);
    
    // Start main loop
    gtk_main();
}