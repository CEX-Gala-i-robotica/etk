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
#define DEFAULT_UI_FONT "assets/fonts/Rambla-Bold.ttf"


#include "ui_main.h"






#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_IMPLEMENTATION
#include <nuklear.h>

#define NK_XCB_CAIRO_IMPLEMENTATION
#include <nuklear_xcb.h>



#include "extra_components/style.c"
#ifdef UI_DEVEL
    #include "extra_components/overview.c"
    #include "extra_components/style_configurator.c"
    #include "extra_components/node_editor.c"
    #include "extra_components/canvas.c"
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
    background = nk_rgb(0, 0, 0);
    
    xcb_ctx = nk_xcb_init("ETK", 20, 20, 1500, 950);
    cairo_ctx = nk_cairo_init(&background, NULL, 0, nk_xcb_create_cairo_surface(xcb_ctx));
    cairo_ctx = nk_cairo_init(&background, DEFAULT_UI_FONT, 18, nk_xcb_create_cairo_surface(xcb_ctx));
    font = nk_cairo_default_font(cairo_ctx);
    ctx = malloc(sizeof(struct nk_context));
    nk_init_default(ctx, font);
    
    // Set default theme
    set_style(ctx, THEME_DRACULA);
}


void ui_main(int ac, char *av[])
{
    log_info("UI Main");
    
    int running = 1;
    int events;
    
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
            nk_cairo_damage(cairo_ctx);
        }
        if(events & NK_XCB_EVENT_RESIZED)
        {
            nk_xcb_resize_cairo_surface(xcb_ctx, nk_cairo_surface(cairo_ctx));
        }

        /* Small demo */
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
#endif

        /* -------------- Predefined examples from nuklear ---------------- */
        
#ifdef UI_DEVEL
        overview(ctx);
        style_configurator(ctx, color_table);
        node_editor(ctx);
        canvas(ctx);
#endif
        render_main_window(ctx);
        
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