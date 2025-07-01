#include <gtk/gtk.h>
#include <librsvg/rsvg.h>






#include "entry.h"
#include "theme.h"










GtkWidget *main_window;


GtkWidget *settings_icon = NULL;
GtkWidget *start_icon = NULL;
GtkWidget *stop_icon = NULL;

int tree_item_index = 1;

/*
Internal functions
....
*/


void load_css_theme()
{
    GtkCssProvider *css_provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    // Load CSS from file
    GError *error = NULL;
    
    //gtk_css_provider_load_from_data(css_provider, css_theme, -1, NULL);
    
    if (!gtk_css_provider_load_from_file(css_provider,  g_file_new_for_path("assets/etk-gtk.css"), &error))
    {
        g_warning("Failed to load CSS file: %s", error->message);
        g_error_free(error);
        g_object_unref(css_provider);
        return;
    }
    
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    g_object_unref(css_provider);
}

GdkPixbuf *load_svg_icon(RsvgHandle *svg_handle)
{
    GdkPixbuf *img = NULL;
    GError *err;
    
    
    if(!svg_handle)
    {
        g_printerr("Failed to load svg icon ! msg: %s", err->message);
        g_error_free(err);
        return NULL;
    }
    else
    {
        gdouble svg_width = 0, svg_height = 0;
        gboolean has_size = rsvg_handle_get_intrinsic_size_in_pixels(svg_handle, &svg_width, &svg_height);
        
        // Set desired size
        int width = (has_size && svg_width > 0) ? (int)(svg_width + 0.5) : 32;
        int height = (has_size && svg_height > 0) ? (int)(svg_height + 0.5) : 32;
        
        GdkPixbuf *temp_pixbuf = rsvg_handle_get_pixbuf_sub(svg_handle, NULL);
        if(!temp_pixbuf)
        {
            g_printerr("Failed to render SVG to Pixel Buffer !!\n");
            g_object_unref(svg_handle);
        }
        else
        {
            img = gdk_pixbuf_scale_simple(temp_pixbuf, ICON_WIDTH, ICON_HEIGHT, GDK_INTERP_BILINEAR);
        }
        g_object_unref(temp_pixbuf);
    }
    
    return img;    
}

void load_assets()
{
    
    GError *err = NULL;
    RsvgHandle *i_settings_hnd = rsvg_handle_new_from_file("assets/icons/settings.svg", &err);
    RsvgHandle *i_start_hnd = rsvg_handle_new_from_file("assets/icons/start.svg", &err);
    RsvgHandle *i_stop_handle = rsvg_handle_new_from_file("assets/icons/stop-solid.svg", &err);
    

    settings_icon = gtk_image_new_from_pixbuf(load_svg_icon(i_settings_hnd));
    start_icon = gtk_image_new_from_pixbuf(load_svg_icon(i_start_hnd));
    stop_icon = gtk_image_new_from_pixbuf(load_svg_icon(i_stop_handle));
    
    
    g_object_unref(i_settings_hnd);
    g_object_unref(i_start_hnd);
    g_object_unref(i_stop_handle);
}


// Button click handlers
void on_button_clicked(GtkWidget *button, gpointer data)
{
    const char *label = gtk_button_get_label(GTK_BUTTON(button));
    g_print("Button clicked: %s\n", label);
}

void on_settings_click(GtkWidget *btn, gpointer data)
{
    //g_print("Settings clicked !!!\n");
    static GtkWidget *settings_window = NULL;
    GtkWidget *stack;
    
    
    // Make sure no extra setting window can be opened after clicking the setting button again (Only 1 widnow condition)
    if(settings_window == NULL)
    {
        settings_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(settings_window), "Setări");
        gtk_window_set_default_size(GTK_WINDOW(settings_window), 700, 700);
        gtk_container_set_border_width(GTK_CONTAINER(settings_window), 20);
        gtk_style_context_add_class(gtk_widget_get_style_context(settings_window), "main-window");
        g_signal_connect(settings_window, "destroy", G_CALLBACK(gtk_widget_destroyed), &settings_window);
        
        GtkWidget *headerbar = gtk_header_bar_new();
        gtk_header_bar_set_title(GTK_HEADER_BAR(headerbar), "ETK - Setări");
        gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(headerbar), TRUE);
        gtk_widget_set_name(headerbar, "window-header");
        
        gtk_window_set_titlebar(GTK_WINDOW(settings_window), headerbar);
    
    
    
        // UI Stuff here
        
        GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        
        stack = gtk_stack_new();
        gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
        gtk_stack_set_transition_duration(GTK_STACK(stack), 500);
        
        GtkWidget *label1 = gtk_label_new("This is Page 1");
        GtkWidget *label2 = gtk_label_new("This is Page 2");
        GtkWidget *label3 = gtk_label_new("sdjfdsjkfhdshfkdsj");
        
        gtk_stack_add_titled(GTK_STACK(stack), label1, "page1", "Setări Generale");
        gtk_stack_add_titled(GTK_STACK(stack), label2, "page2", "Unelte Interne");
        gtk_stack_add_titled(GTK_STACK(stack), label3, "page3", "Date Statistice");
        
        GtkWidget *switcher = gtk_stack_switcher_new();
        gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(switcher), GTK_STACK(stack));
        gtk_style_context_add_class(gtk_widget_get_style_context(switcher), "tab-switcher");
        
        gtk_box_pack_start(GTK_BOX(vbox), switcher, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox), stack, TRUE, TRUE, 0);
        
        gtk_container_add(GTK_CONTAINER(settings_window), vbox);
        
        
        
        // Show all widgets
        gtk_widget_show_all(settings_window);
    } // Only 1 window condition
    else
    {
        gtk_window_present(GTK_WINDOW(settings_window));
    }
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

void on_treeview_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data)
{
    if(gtk_tree_view_row_expanded(treeview, path)) gtk_tree_view_collapse_row(treeview, path);
    else
        gtk_tree_view_expand_row(treeview, path, FALSE);
}

void ui_structure()
{
    GtkWidget *vbox;
    GtkWidget *listbox;
    GtkWidget *hbox;
    GtkWidget *hbox_btn_settings;
    GtkWidget *hbox_top;
    GtkWidget *hbox_buttons;
    GtkWidget *btn_run_probe;
    GtkWidget *btn_stop_probe;
    GtkWidget *btn_settings;
    GtkWidget *scrolled_window;
    int i;
    
    const int LISTBOX_WIDTH = 350;
    const int BUTTON_WIDTH = 100;
    const int BUTTON_HEIGHT = 40;

    
    // Main vertical box
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(main_window), vbox);

    
    hbox_btn_settings = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox_btn_settings, FALSE, FALSE, 0);
    
    // Top horizontal box for listbox and spacer
    hbox_top = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox_top, TRUE, TRUE, 0);

    
    
    
    btn_settings = gtk_button_new_with_label("");
    gtk_button_set_image(GTK_BUTTON(btn_settings), settings_icon);
    gtk_button_set_always_show_image(GTK_BUTTON(btn_settings), TRUE);
    gtk_style_context_add_class(gtk_widget_get_style_context(btn_settings), "normal-btn");
    g_signal_connect(btn_settings, "clicked", G_CALLBACK(on_settings_click), NULL);
    gtk_widget_set_tooltip_text(btn_settings, "Deschide setările într-o fereastră separată");
    gtk_box_pack_start(GTK_BOX(hbox_btn_settings), btn_settings, FALSE, FALSE, 0);
    
    
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(scrolled_window, LISTBOX_WIDTH, -1); // fixed width, expands vertically
    gtk_box_pack_start(GTK_BOX(hbox_top), scrolled_window, FALSE, TRUE, 0);

    GtkWidget *spacer = gtk_label_new(NULL);
    gtk_box_pack_start(GTK_BOX(hbox_top), spacer, TRUE, TRUE, 0);
    

/*
Component list tree view
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
    
    g_signal_connect(treeview, "row-activated", G_CALLBACK(on_treeview_row_activated), NULL);
    
    
    
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    g_signal_connect(selection, "changed", G_CALLBACK(on_tree_selection_changed), NULL);
    
    // Only add the name column
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(treeview), FALSE);
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes("Component list", renderer, "text", 0, NULL); // 0 is the string column
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    gtk_container_add(GTK_CONTAINER(scrolled_window), treeview);
    
/*
Run / Stop buttons
*/

    // Horizontal box for buttons
    hbox_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(vbox), hbox_buttons, FALSE, FALSE, 0);
    
    // Run Probe button
    btn_run_probe = gtk_button_new_with_label("");
    gtk_button_set_image(GTK_BUTTON(btn_run_probe), start_icon);
    gtk_button_set_always_show_image(GTK_BUTTON(btn_run_probe), TRUE);
    gtk_style_context_add_class(gtk_widget_get_style_context(btn_run_probe), "normal-btn");
    g_signal_connect(btn_run_probe, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_widget_set_tooltip_text(btn_run_probe, "Efectuează test automat");
    gtk_box_pack_start(GTK_BOX(hbox_buttons), btn_run_probe, FALSE, FALSE, 0);

    // Stop Probe button
    btn_stop_probe = gtk_button_new_with_label("");
    gtk_button_set_image(GTK_BUTTON(btn_stop_probe), stop_icon);
    gtk_button_set_always_show_image(GTK_BUTTON(btn_stop_probe), TRUE);
    gtk_style_context_add_class(gtk_widget_get_style_context(btn_stop_probe), "gray-btn");
    g_signal_connect(btn_stop_probe, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_widget_set_tooltip_text(btn_stop_probe, "Oprește testul automat");
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
    
    GtkWidget *headerbar = gtk_header_bar_new();
    gtk_header_bar_set_title(GTK_HEADER_BAR(headerbar), "ETK"); // plsss I want ETK as official name
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(headerbar), TRUE);
    gtk_widget_set_name(headerbar, "window-header");
    
    gtk_window_set_titlebar(GTK_WINDOW(main_window), headerbar);
    
    load_assets();
    
    load_css_theme();
    
    
    ui_structure();
    
    
    // Connect window destroy signal
    g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Show all widgets
    gtk_widget_show_all(main_window);
    
    // Start main loop
    gtk_main();
    
    // Free up stuff
    
    //g_object_unref(handle);
    //g_object_unref(pixbuf);
    //g_object_unref(settings_icon);
    //g_object_unref(start_icon);
    //g_object_unref(stop_icon);
}