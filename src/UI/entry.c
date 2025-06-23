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

enum {
    COL_NAME,
    COL_COLOR,
    COL_CLASS, // CSS class for styling
    NUM_COLS
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

static void set_row_css_class(GtkTreeViewColumn *col, GtkCellRenderer *renderer, GtkTreeModel *model, GtkTreeIter *iter, gpointer data)
{
    gchar *css_class;
    gtk_tree_model_get(model, iter, COL_CLASS, &css_class, -1);

    if(css_class && *css_class)
    {
        g_object_set(renderer, "cell-background-set", TRUE, NULL);
        // Set a style class on the row via GtkCellRenderer's "style" property
        // But GtkCellRendererText doesn't have a style property, so we use "cell-background" as a workaround
        // Alternatively, you can use GtkTreeViewRowSeparatorFunc or custom widgets in GTK4
        // Here, we just set a tag in the model and use CSS selectors on the row
        // But for GTK3, per-row CSS classes are not directly supported, so we use cell-background
        // For demonstration, let's set cell background color via CSS class
        // But since that's not possible, we set "cell-background" property directly
        // (If you want to use CSS classes, you need to use GtkListBox in GTK3. For TreeView, it's limited.)
        // So, let's map class to color:
        if(g_strcmp0(css_class, "red-row") == 0)
            g_object_set(renderer, "cell-background", "#ffcccc", NULL);
        else if(g_strcmp0(css_class, "green-row") == 0)
            g_object_set(renderer, "cell-background", "#ccffcc", NULL);
        else if(g_strcmp0(css_class, "blue-row") == 0)
            g_object_set(renderer, "cell-background", "#ccccff", NULL);
        else
            g_object_set(renderer, "cell-background", NULL, NULL);
    }
    else
    {
        g_object_set(renderer, "cell-background", NULL, NULL);
    }
    g_free(css_class);
}





static void
set_row_color(GtkTreeViewColumn *col,
              GtkCellRenderer   *renderer,
              GtkTreeModel      *model,
              GtkTreeIter       *iter,
              gpointer           data)
{
    gchar *color;
    gtk_tree_model_get(model, iter, COL_COLOR, &color, -1);

    if (color && *color) {
        g_object_set(renderer,
                     "cell-background", color,
                     "cell-background-set", TRUE,
                     NULL);
    } else {
        g_object_set(renderer,
                     "cell-background-set", FALSE,
                     NULL);
    }
    g_free(color);
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
// Create TreeStore
GtkTreeStore *store = gtk_tree_store_new(NUM_COLS, G_TYPE_STRING, G_TYPE_STRING);

    GtkTreeIter iter1, iter2, iter3;
    GtkTreeIter child1, child2;

    // Fruits
    gtk_tree_store_append(store, &iter1, NULL);
    gtk_tree_store_set(store, &iter1,
                       COL_NAME, "Fruits",
                       COL_COLOR, "#ffcccc",
                       -1);

    gtk_tree_store_append(store, &child1, &iter1);
    gtk_tree_store_set(store, &child1,
                       COL_NAME, "Apple",
                       COL_COLOR, "",
                       -1);

    gtk_tree_store_append(store, &child2, &iter1);
    gtk_tree_store_set(store, &child2,
                       COL_NAME, "Banana",
                       COL_COLOR, "",
                       -1);

    // Vegetables
    gtk_tree_store_append(store, &iter2, NULL);
    gtk_tree_store_set(store, &iter2,
                       COL_NAME, "Vegetables",
                       COL_COLOR, "#ccffcc",
                       -1);

    gtk_tree_store_append(store, &child1, &iter2);
    gtk_tree_store_set(store, &child1,
                       COL_NAME, "Carrot",
                       COL_COLOR, "",
                       -1);

    gtk_tree_store_append(store, &child2, &iter2);
    gtk_tree_store_set(store, &child2,
                       COL_NAME, "Broccoli",
                       COL_COLOR, "",
                       -1);

    // Drinks
    gtk_tree_store_append(store, &iter3, NULL);
    gtk_tree_store_set(store, &iter3,
                       COL_NAME, "Drinks",
                       COL_COLOR, "#ccccff",
                       -1);

    gtk_tree_store_append(store, &child1, &iter3);
    gtk_tree_store_set(store, &child1,
                       COL_NAME, "Water",
                       COL_COLOR, "",
                       -1);

    gtk_tree_store_append(store, &child2, &iter3);
    gtk_tree_store_set(store, &child2,
                       COL_NAME, "Juice",
                       COL_COLOR, "",
                       -1);

    GtkWidget *treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(treeview), FALSE);

    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(
        "Name", renderer, "text", COL_NAME, NULL);

    gtk_tree_view_column_set_cell_data_func(column, renderer, set_row_color, NULL, NULL);

    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
        // Already have a scrolled window
        gtk_container_add(GTK_CONTAINER(scrolled_window), treeview);
    
        //gtk_container_add(GTK_CONTAINER(scrolled_window), scrolled);
 
    

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