#include <gtk/gtk.h>






#include "entry.h"
#include "theme.h"











GtkWidget *main_window;

/*
Internal functions
....
*/


const char *items[] = 
{
    "Servo",
    "Stepper",
    "H Bridge L298N",
    "DHT",
    "LCD I2C",
    "MPU 6500",
    "Ultrasonic",
    "Keypad 2x4",
    "Keypad 4x4",
    "Keypad 3x4",
    "Infrared",
    "LED Matrix",
    "Water Level",
    "Soil Moisture",
    "Speed Sensor",
    "Gas Detector",
    "Smoke Detector",
    "Microphone",
    "PH Meter",
    "Hall Sensor",
    "Flow Meter",
    "Potentiometer",
    "Photoresistor",
    "Stepper Motor ULN2003",
    "RFID RC522",
    "Joystick X2",
    "IR Remote",
    "PCA 9685",
    "A4988 Stepper",
    "RT Clock DS1302",
    "RT Clock DS3231",
    "RTClock DS1307",   
};

void load_css_theme()
{
    GtkCssProvider *css_provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    // Load CSS from file
    GError *error = NULL;
    
    //gtk_css_provider_load_from_data(css_provider, css_theme, -1, NULL);
    
    if (!gtk_css_provider_load_from_file(css_provider,  g_file_new_for_path("mpp-box-theme.css"), &error))
    {
        g_warning("Failed to load CSS file: %s", error->message);
        g_error_free(error);
        g_object_unref(css_provider);
        return;
    }
    
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
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
    
    if(gtk_style_context_has_class(context, "btn-primary"))
    {
        gtk_style_context_remove_class(context, "btn-primary");
        gtk_style_context_add_class(context, "btn-danger");
        gtk_button_set_label(GTK_BUTTON(target_button), "Danger Button");
    }
    else
    {
        gtk_style_context_remove_class(context, "btn-danger");
        gtk_style_context_add_class(context, "btn-primary");
        gtk_button_set_label(GTK_BUTTON(target_button), "Primary Button");
    }
}



void ui_structure()
{
    GtkWidget *vbox;
    GtkWidget *listbox;
    GtkWidget *hbox;
    GtkWidget *hbox_top;
    GtkWidget *hbox_buttons;
    GtkWidget *btn_run_probe;
    GtkWidget *btn_stop_probe;
    //GtkWidget *row;
    GtkWidget *scrolled_window;
    int i;
    
    const int LISTBOX_WIDTH = 250;
    const int BUTTON_WIDTH = 100;
    const int BUTTON_HEIGHT = 40;

    
    // Main vertical box
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(main_window), vbox);

    
    // Top horizontal box for listbox and spacer
    hbox_top = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox_top, TRUE, TRUE, 0);
    
    
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(scrolled_window, LISTBOX_WIDTH, -1); // fixed width, expands vertically
    gtk_box_pack_start(GTK_BOX(hbox_top), scrolled_window, FALSE, TRUE, 0);

    GtkWidget *spacer = gtk_label_new(NULL);
    gtk_box_pack_start(GTK_BOX(hbox_top), spacer, TRUE, TRUE, 0);
    

/*
Component list tree view

Todo:
- Add & organize the tree vew of electronic components
- Apply style for each of the item categories
*/
    GtkTreeStore *store = gtk_tree_store_new(2, G_TYPE_STRING, G_TYPE_INT);
    
    GtkTreeIter parent, child;
    
    // Parent 1
    gtk_tree_store_append(store, &parent, NULL);
    gtk_tree_store_set(store, &parent, 0, "Alice", 1, 30, -1);
    // Child of Alice
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Alice's Child 1", 1, 5, -1);
    
    // Parent 2
    gtk_tree_store_append(store, &parent, NULL);
    gtk_tree_store_set(store, &parent, 0, "Bob", 1, 25, -1);
    // Child of Bob
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Bob's Child 1", 1, 3, -1);
    
    GtkWidget *treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    
    // Only add the name column
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(treeview), FALSE);
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes("Component list", renderer, "dummy", 0, NULL); // 0 is the string column
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    gtk_container_add(GTK_CONTAINER(scrolled_window), treeview);

    // Horizontal box for buttons
    hbox_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(vbox), hbox_buttons, FALSE, FALSE, 0);
    
    // Run Probe button
    btn_run_probe = gtk_button_new_with_label("Run Automatic Probe");
    gtk_widget_set_size_request(btn_run_probe, BUTTON_WIDTH, BUTTON_HEIGHT);
    gtk_style_context_add_class(gtk_widget_get_style_context(btn_run_probe), "normal-btn");
    g_signal_connect(btn_run_probe, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(hbox_buttons), btn_run_probe, FALSE, FALSE, 0);

    // Stop Probe button
    btn_stop_probe = gtk_button_new_with_label("Stop Probe");
    gtk_widget_set_size_request(btn_stop_probe, BUTTON_WIDTH, BUTTON_HEIGHT);
    gtk_style_context_add_class(gtk_widget_get_style_context(btn_stop_probe), "gray-btn");
    g_signal_connect(btn_stop_probe, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(hbox_buttons), btn_stop_probe, FALSE, FALSE, 0);
}


void ui_entry(int ac, char *av[])
{
    gtk_init(&ac, &av);
    
    main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(main_window), "MPP Box");
    gtk_window_set_default_size(GTK_WINDOW(main_window), 500, 500);
    gtk_container_set_border_width(GTK_CONTAINER(main_window), 20);
    gtk_style_context_add_class(gtk_widget_get_style_context(main_window), "main-window");
    
    load_css_theme();
    
    
    ui_structure();
    
    
    // Connect window destroy signal
    g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Show all widgets
    gtk_widget_show_all(main_window);
    
    // Start main loop
    gtk_main();
}