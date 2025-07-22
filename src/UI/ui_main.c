/*
!!! WARNING !!!
The entire UI will get a full redesign using Nuklear due to some GTK related issues
*/


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <stddef.h>
#include <stdbool.h>

#include <log_c/log.h>





#define UI_DEVEL


#include "ui_main.h"






#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_IMPLEMENTATION
#include <nuklear.h>

#define NK_XCB_CAIRO_IMPLEMENTATION
#include <nuklear_xcb.h>



#include "components/dev_demos/style.c"
// Here are some predefined components that can be helpful for UI development
#ifdef UI_DEVEL
    #include "components/dev_demos/overview.c"
    #include "components/dev_demos/style_configurator.c"
    #include "components/dev_demos/node_editor.c"
    #include "components/dev_demos/canvas.c"
#endif

#include "main_window.h"


#include "default_theme.h"


#include "../config_utils.h"
#include "../tests.h"




struct nk_xcb_context *xcb_ctx;
struct nk_color background;
struct nk_cairo_context *cairo_ctx;
struct nk_user_font *font;
struct nk_context* ctx;


Configuration live_config;

Configuration default_config;


//static Configuration parsed_config;


/*
Internal functions
....
*/


void load_assets()
{
    log_warn("load_assets() has no practical implementation !!!!");
    // Reimplementation is under way...
}




void ui_init()
{
    log_info("UI Init");
    
    
    background = nk_rgb(0, 0, 0); // Background color of the x11 window
    
    xcb_ctx = nk_xcb_init("ETK", 20, 20, 1500, 950); //Create a rendering window with cairo via xcb
    
    // Create rendering surface using a custom font (DEFAULT_UI_FONT)
    cairo_ctx = nk_cairo_init(&background, DEFAULT_UI_FONT, 18, nk_xcb_create_cairo_surface(xcb_ctx));
    font = nk_cairo_default_font(cairo_ctx); // Set the loaded font
    ctx = malloc(sizeof(struct nk_context));
    nk_init_default(ctx, font); // Initialize the nuklear context with the font
    
    // Set default theme
    set_style(ctx, parsed_config.color_theme);
}


void ui_main(int ac, char *av[])
{
    log_info("UI Main");
    
    
    // Set default settings
    
    // Maybe not all this is necessary...
    default_config.loop_mode                 = true;
    default_config.always_show_plots         = true;
    default_config.autosave_csv              = true;
    default_config.logs_2_file               = false;
    default_config.internal_buzzer           = true;
    default_config.show_power_status         = true;
    default_config.save_ui_state             = false;
    default_config.always_clear_gpio_on_exit = true;
    default_config.virtual_osc               = false;
    default_config.color_theme               = 5;
    
    if(!config_exists())
    {
        log_warn("No config was found. Using defaults");
        save_config(default_config); // Most importantly save the deafult confuguration to json to prevent cJSON parsing errors which result in exit errors...
        live_config = default_config; // even If I already assigned the default config to the continusly changing configuration
    }
    else
    {
        parsed_config = load_config();
        live_config = parsed_config;
    }
    
    
    //Todo: implement default settings
    current_theme = parsed_config.color_theme;
    
    int events;
    
    // This is required for switching in between multiple color themes (defined in style.c)
    static struct nk_color color_table[NK_COLOR_COUNT];
    memcpy(color_table, nk_default_color_style, sizeof(color_table));
    
    
    
    ui_init();

    
    /* UI Mainloop */
    log_info("UI loop");
    while(1)
    {
        /* Events */
        events = nk_xcb_handle_event(xcb_ctx, ctx);
        if(events & NK_XCB_EVENT_STOP)
        {
            break;
        }
        if(events & NK_XCB_EVENT_PAINT)
        {
            // Not sure but I think this is resposnable for clearing the previous frame...
            nk_cairo_damage(cairo_ctx);
        }
        if(events & NK_XCB_EVENT_RESIZED)
        {
            // Always keep the rendering surface sized as the window
            nk_xcb_resize_cairo_surface(xcb_ctx, nk_cairo_surface(cairo_ctx));
        }

        // This is just a small GUI demo using nuklear
#ifdef UI_DEVEL
        if(nk_begin(ctx, "[Dev] - Demo", nk_rect(50, 50, 200, 200), NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
        {
            enum {EASY, HARD};
            static int op = EASY;
            static int property = 20;

            nk_layout_row_static(ctx, 30, 80, 1);
            if (nk_button_label(ctx, "button"))
                fprintf(stdout, "button pressed\n");
            nk_layout_row_dynamic(ctx, 30, 2);
            if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
            if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;
            nk_layout_row_dynamic(ctx, 25, 1);
            nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);
        }
        nk_end(ctx);
        if(nk_window_is_hidden(ctx, "[Dev] - Demo"))
        {
            break;
        }
        
        if(nk_begin(ctx, "[Dev] - unicodes", nk_rect(230, 230, 230, 95), NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
        {
            nk_layout_row_static(ctx, 30, 80, 1);
            if (nk_button_label(ctx, "ă Ă î Î â Â ș Ș ț Ț"))
                fprintf(stdout, "unicode button pressed\n");
        }
        nk_end(ctx);
        if(nk_window_is_hidden(ctx, "[Dev] - unicodes"))
        {
            break;
        }
#endif

        /* -------------- Predefined examples from nuklear ---------------- */
  
// Here are more examples      
#ifdef UI_DEVEL
        overview(ctx); // All widgets of nuklear
        style_configurator(ctx, color_table); // Allows full customization of every UI element
        node_editor(ctx);
        canvas(ctx); // Uses the builtin canvas from nuklear
#endif
        render_main_window(ctx);
        
        // Checks if the closing button of the main window was clicked => loop broken -> program exit
        if(is_main_window_exit)
        {
            break;
        }
       
        /* ----------------------------------------- */

        /* Render */
        nk_cairo_render(cairo_ctx, ctx);
        nk_xcb_render(xcb_ctx);
        nk_clear(ctx);
    }

    log_info("UI Mainloop broken");
    nk_free(ctx);
    free(ctx);
    nk_cairo_free(cairo_ctx);
    nk_xcb_free(xcb_ctx);

}