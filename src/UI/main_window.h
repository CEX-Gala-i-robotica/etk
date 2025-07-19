#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H


bool is_main_window_exit = false;

void render_main_window(struct nk_context *ctx)
{
    
    if(nk_begin(ctx, "Main Window", nk_rect(350, 80, 800, 800), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_CLOSABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
    {

        nk_layout_row_static(ctx, 30, 100, 3);
        if(nk_button_label(ctx, "Button"))
            log_info("button pressed");
            
        nk_layout_row_dynamic(ctx, 30, 2);
    }
    nk_end(ctx);

    if(nk_window_is_hidden(ctx, "Main Window"))
    {
        log_info("Closing Main Window");
        is_main_window_exit = true;
    }
}

#endif