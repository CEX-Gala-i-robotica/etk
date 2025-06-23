#include <gtk/gtk.h>






#include "entry.h"
#include "theme.h"










GtkWidget *main_window;

int tree_item_index = 1;

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


void on_tree_selection_changed(GtkTreeSelection *selection, gpointer user_data)
{
    GtkTreeModel *model;
    GtkTreeIter iter;
 
    if(gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        if(!gtk_tree_model_iter_has_child(model, &iter))
        {
            gchar *name = NULL;
            gint value = 0;
            gtk_tree_model_get(model, &iter, 0, &name, 1, &value, -1);
            g_print("Selected leaf: %s (value: %d)\n", name, value);
            g_free(name);
        }
        else
        {
            gtk_tree_selection_unselect_iter(selection, &iter);
        }
    }
}

gboolean row_separator_func(GtkTreeModel *model, GtkTreeIter *iter, gpointer data)
{
    // Return TRUE to draw a separator after this row
    return TRUE;
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
    
    const int LISTBOX_WIDTH = 350;
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
- Apply style for each of the item categories
*/
    
    

    GtkTreeStore *store = gtk_tree_store_new(2, G_TYPE_STRING, G_TYPE_INT);
    
    GtkTreeIter parent, child;
    
    
    // Tree 1
    gtk_tree_store_append(store, &parent, NULL);
    gtk_tree_store_set(store, &parent, 0, "Microcontrolere & Plarforme", 1, 0, -1);
    
    // Items
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Arduino UNO", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Arduino Nano", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Arduino Mega", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Arduino Giga", 1, tree_item_index++, -1);
    
    
    // Tree 2
    gtk_tree_store_append(store, &parent, NULL);
    gtk_tree_store_set(store, &parent, 0, "Module de extensie (Shield)", 1, 25, -1);
    
    // Items
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Simple Shield", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &parent, NULL);
    gtk_tree_store_set(store, &parent, 0, "Display-uri", 1, 25, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "LCD I2C", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "LCD", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "OLED", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "TFT", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "7 Segment Display", 1, tree_item_index++, -1);
    
    
    // Tree 3
    gtk_tree_store_append(store, &parent, NULL);
    gtk_tree_store_set(store, &parent, 0, "Senzori Analogici / Digitali", 1, 25, -1);
    
    // Items
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Ultrasonic HC06", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Receptor Infraroșu", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "DHT", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Detector de gaz", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Detector de fum", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Nivel de apă", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Umiditate Sol", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Senzor de rotații", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Senzor Giroscopic (MPU 6050)", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Senzor de viteză", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Microfon", 1, tree_item_index++, -1);

    
    // Tree 4
    gtk_tree_store_append(store, &parent, NULL);
    gtk_tree_store_set(store, &parent, 0, "Motoare", 1, 25, -1);
    
    // Items
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Servo", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Stepper ULN2003", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Stepper A4988", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Punte H L298N", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Servo PCA9685", 1, tree_item_index++, -1);
 
    
    // Tree 5
    gtk_tree_store_append(store, &parent, NULL);
    gtk_tree_store_set(store, &parent, 0, "Alimentare & Control Tensiune", 1, 25, -1);
    
    
    // Tree 6
    gtk_tree_store_append(store, &parent, NULL);
    gtk_tree_store_set(store, &parent, 0, "Comunicare & Retea", 1, 25, -1);
   
   
    // Tree 7 
    gtk_tree_store_append(store, &parent, NULL);
    gtk_tree_store_set(store, &parent, 0, "Stocare & Interfete", 1, 25, -1);
    
    // Items
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Modul de precizie RTC", 1, tree_item_index++, -1);
   
    
    // Tree 8
    gtk_tree_store_append(store, &parent, NULL);
    gtk_tree_store_set(store, &parent, 0, "Componente Pasive", 1, 25, -1);
    
    // Items
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Modul Tastatură", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Potențiometru", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Modul joystick X2", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Senzor Debit Apă", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Fotorezistor", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Sezor Magnetic (Hall)", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Buzzer", 1, tree_item_index++, -1);

    
    // Tree 9
    gtk_tree_store_append(store, &parent, NULL);
    gtk_tree_store_set(store, &parent, 0, "LED-uri & module", 1, 0, -1);
    
    //Items
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "LED Simplu", 1, tree_item_index++, -1);
    
    gtk_tree_store_append(store, &child, &parent);
    gtk_tree_store_set(store, &child, 0, "Matrice LED", 1, tree_item_index++, -1);
    
    
    
    GtkWidget *treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    
    
    
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    g_signal_connect(selection, "changed", G_CALLBACK(on_tree_selection_changed), NULL);
    
    // Only add the name column
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(treeview), FALSE);
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes("Component list", renderer, "text", 0, NULL); // 0 is the string column
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    gtk_container_add(GTK_CONTAINER(scrolled_window), treeview);

    // Horizontal box for buttons
    hbox_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(vbox), hbox_buttons, FALSE, FALSE, 0);
    
    // Run Probe button
    btn_run_probe = gtk_button_new_with_label("Efectuează Probă Automată");
    gtk_widget_set_size_request(btn_run_probe, BUTTON_WIDTH, BUTTON_HEIGHT);
    gtk_style_context_add_class(gtk_widget_get_style_context(btn_run_probe), "normal-btn");
    g_signal_connect(btn_run_probe, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(hbox_buttons), btn_run_probe, FALSE, FALSE, 0);

    // Stop Probe button
    btn_stop_probe = gtk_button_new_with_label("Anulează Probă");
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
    gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 500);
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