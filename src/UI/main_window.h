#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "../tests.h"
#include "../config_utils.h"







bool is_main_window_exit = false;
static int current_tab = 0;

static int selected_index = -1;
int is_selected;



static int current_theme = 5;
static const char* themes[] = 
{
    "Black", 
    "White", 
    "Red", 
    "Blue", 
    "Dark", 
    "Dracula", 
    "Catppucin Latte", 
    "Catppucin Frappe", 
    "Catppucin Macchiato", 
    "Catppucin Mocha"
};


void tab_button(struct nk_context *ctx, const char *label, int id, int *current_tab)
{
    struct nk_style_button original = ctx->style.button;
    
    struct nk_color btn_normal = ctx->style.button.normal.data.color;
    struct nk_color btn_hover  = ctx->style.button.hover.data.color;
    struct nk_color btn_active = ctx->style.button.active.data.color;

    

    if(*current_tab == id)
    {
        // Modify button style for the active tab
        ctx->style.button.normal = nk_style_item_color(btn_hover);
        ctx->style.button.hover  = nk_style_item_color(btn_active);
        ctx->style.button.active = nk_style_item_color(btn_active);
    }

    if(nk_button_label(ctx, label))
    {
        *current_tab = id;
    }

    // Restore original button style
    ctx->style.button = original;
}

void add_tree_item(struct nk_context *ctx, const char *label, int id)
{
    is_selected = (selected_index == id);
    if(nk_selectable_label(ctx, label, NK_TEXT_LEFT, &is_selected))
    {
        selected_index = id;
    }
}

void render_main_window(struct nk_context *ctx)
{
    
    
    //set_style(ctx, current_theme);
    //log_info("cfg theme: %d", parsed_config.color_theme);
    
    if(nk_begin(ctx, "Panou de Control", nk_rect(350, 80, 800, 800), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_CLOSABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
    {
        nk_layout_row_dynamic(ctx, 30, 3); // Three tab buttons side by side
            
        tab_button(ctx, "Teste", 0, &current_tab);
        tab_button(ctx, "Date în timp real", 1, &current_tab);
        tab_button(ctx, "Setări", 2, &current_tab);
        // ----------------------------------
        nk_layout_row_dynamic(ctx, 10, 1); // Main tab content
        if(current_tab == 0)
        {
            nk_layout_row_static(ctx, 400, 400, 10);
            if(nk_group_begin(ctx, "Group", NK_WINDOW_BORDER))
            {
                if(nk_tree_push(ctx, NK_TREE_NODE, "Microcontrolere și platforme", NK_MINIMIZED))
                {
                    add_tree_item(ctx, "Arduino Uno",  CT_ARDUINO_UNO);
                    add_tree_item(ctx, "Arduino Nano", CT_ARDUINO_NANO);
                    add_tree_item(ctx, "Arduino Mega", CT_ARDUINO_MEGA);
                    add_tree_item(ctx, "Arduino Giga", CT_ARDUINO_GIGA);
                    
                    nk_tree_pop(ctx);
                }
                
                if(nk_tree_push(ctx, NK_TREE_NODE, "Module de extensie (Shield)", NK_MINIMIZED))
                {
                    add_tree_item(ctx, "Temp", 100);
                    
                    nk_tree_pop(ctx);
                }
                
                if(nk_tree_push(ctx, NK_TREE_NODE, "Displai-uri", NK_MINIMIZED))
                {
                    add_tree_item(ctx, "LCD I2C", CT_LCD_I2C);
                    add_tree_item(ctx, "LCD",     CT_LCD);
                    add_tree_item(ctx, "OLED",    CT_OLED);
                    add_tree_item(ctx, "TFT",     CT_TFT);
                    add_tree_item(ctx, "Display numeric cu 7 segmente", CT_SEVEN_SEG_DISPLAY);
                    
                    nk_tree_pop(ctx);
                }
                
                if(nk_tree_push(ctx, NK_TREE_NODE, "Senzori Analogici / Digitali", NK_MINIMIZED))
                {
                    add_tree_item(ctx, "Senzor de distanță HC06",   CT_ULTRASONIC_HC06);
                    add_tree_item(ctx, "Receptor infraroșu",        CT_INFRARED);
                    add_tree_item(ctx, "DHT",                       CT_DHT);
                    add_tree_item(ctx, "Detector de gaz",           CT_GAS_SENSOR);
                    add_tree_item(ctx, "Detector de fum",           CT_SMOKE_DETECTOR);
                    add_tree_item(ctx, "Nivel de apă",              CT_WATER_LEVEL);
                    add_tree_item(ctx, "Umiditate Sol",             CT_SOIL_MOISTURE);
                    add_tree_item(ctx, "Senzor de rotații",         CT_SPEED_SENSOR);
                    add_tree_item(ctx, "Senzor Giroscopic MPU6050", CT_MPU6050);
                    add_tree_item(ctx, "Senzor de Viteză", 500);
                    add_tree_item(ctx, "Microfon",                  CT_MICROPHONE);
                    
                    nk_tree_pop(ctx);
                }
                
                if(nk_tree_push(ctx, NK_TREE_NODE, "Motoare", NK_MINIMIZED))
                {
                    add_tree_item(ctx, "Servo",                   CT_SERVO);
                    add_tree_item(ctx, "Stepper ULN2003",         CT_STEPPER_MOTOR_ULN2003);
                    add_tree_item(ctx, "Stepper A4988 / DRV8825", CT_A4988_DRIVER);
                    add_tree_item(ctx, "Punte H L298N",           CT_H_BRIDGE_L298N);
                    add_tree_item(ctx, "Servo PCA9685",           CT_PCA9685);
                    
                    nk_tree_pop(ctx);
                }
                
                if(nk_tree_push(ctx, NK_TREE_NODE, "Alimentare și control tensiune sau voltaj", NK_MINIMIZED))
                {
                    add_tree_item(ctx, "Temp", 502);
                    
                    nk_tree_pop(ctx);
                }
                
                if(nk_tree_push(ctx, NK_TREE_NODE, "Comunicație și rețea", NK_MINIMIZED))
                {
                    add_tree_item(ctx, "Temp", 504);
                    
                    nk_tree_pop(ctx);
                }
                
                if(nk_tree_push(ctx, NK_TREE_NODE, "Interfețe", NK_MINIMIZED))
                {
                    add_tree_item(ctx, "Modul de ceas (Real Time Clock)", 504);
                    
                    nk_tree_pop(ctx);
                }
                
                if(nk_tree_push(ctx, NK_TREE_NODE, "Componente Pasive", NK_MINIMIZED))
                {
                    add_tree_item(ctx, "Modul Tastatură", 550);
                    add_tree_item(ctx, "Potențiometru", CT_POTENTIOMETER);
                    add_tree_item(ctx, "Modul joystick (2 axe)", CT_JOYSTICK_X2);
                    add_tree_item(ctx, "Senzor debit apă", CT_FLOW_METER);
                    add_tree_item(ctx, "Fotorezitsor", CT_PHOTORESISTOR);
                    add_tree_item(ctx, "Senzor magnetic (Hall)", CT_HALL_SENSOR);
                    add_tree_item(ctx, "Buzzer", 505);
                    
                    nk_tree_pop(ctx);
                }
                nk_group_end(ctx);
            }
        }
        else if(current_tab == 1)
        {
            //nk_label(ctx, "This is Tab 2", NK_TEXT_LEFT);
            // Copied the builtin demo but that's not enough...
            float id = 0;
            static int col_index = -1;
            static int line_index = -1;
            static nk_bool show_markers = nk_true;
            float step = (2*3.141592654f) / 32;

            int i;
            int index = -1;

            /* line chart */
            id = 0;
            index = -1;
            nk_layout_row_dynamic(ctx, 27, 1);
            nk_checkbox_label(ctx, "Show markers", &show_markers);
            nk_layout_row_dynamic(ctx, 100, 1);
            ctx->style.chart.show_markers = show_markers;
            if(nk_chart_begin(ctx, NK_CHART_LINES, 32, -1.0f, 1.0f))
            {
                for(i = 0; i < 32; ++i)
                {
                    nk_flags res = nk_chart_push(ctx, (float)cos(id));
                    if(res & NK_CHART_HOVERING)
                        index = (int)i;
                    if(res & NK_CHART_CLICKED)
                        line_index = (int)i;
                    id += step;
                }
                nk_chart_end(ctx);
            }

            if(index != -1)
                nk_tooltipf(ctx, "Value: %.2f", (float)cos((float)index*step));
            if(line_index != -1)
            {
                nk_layout_row_dynamic(ctx, 20, 1);
                nk_labelf(ctx, NK_TEXT_LEFT, "Selected value: %.2f", (float)cos((float)index*step));
            }

            /* column chart */
            nk_layout_row_dynamic(ctx, 100, 1);
            if(nk_chart_begin(ctx, NK_CHART_COLUMN, 32, 0.0f, 1.0f))
            {
                for(i = 0; i < 32; ++i)
                {
                    nk_flags res = nk_chart_push(ctx, (float)fabs(sin(id)));
                    if(res & NK_CHART_HOVERING)
                        index = (int)i;
                    if(res & NK_CHART_CLICKED)
                        col_index = (int)i;
                    id += step;
                }
                nk_chart_end(ctx);
            }
            if(index != -1)
                nk_tooltipf(ctx, "Value: %.2f", (float)fabs(sin(step * (float)index)));
            if(col_index != -1)
            {
                nk_layout_row_dynamic(ctx, 20, 1);
                nk_labelf(ctx, NK_TEXT_LEFT, "Selected value: %.2f", (float)fabs(sin(step * (float)col_index)));
            }

            /* mixed chart */
            nk_layout_row_dynamic(ctx, 100, 1);
            if(nk_chart_begin(ctx, NK_CHART_COLUMN, 32, 0.0f, 1.0f))
            {
                nk_chart_add_slot(ctx, NK_CHART_LINES, 32, -1.0f, 1.0f);
                nk_chart_add_slot(ctx, NK_CHART_LINES, 32, -1.0f, 1.0f);
                for(id = 0, i = 0; i < 32; ++i)
                {
                    nk_chart_push_slot(ctx, (float)fabs(sin(id)), 0);
                    nk_chart_push_slot(ctx, (float)cos(id), 1);
                    nk_chart_push_slot(ctx, (float)sin(id), 2);
                    id += step;
                }
            }
            nk_chart_end(ctx);

            /* mixed colored chart */
            nk_layout_row_dynamic(ctx, 100, 1);
            if(nk_chart_begin_colored(ctx, NK_CHART_LINES, nk_rgb(255,0,0), nk_rgb(150,0,0), 32, 0.0f, 1.0f))
            {
                nk_chart_add_slot_colored(ctx, NK_CHART_LINES, nk_rgb(0,0,255), nk_rgb(0,0,150),32, -1.0f, 1.0f);
                nk_chart_add_slot_colored(ctx, NK_CHART_LINES, nk_rgb(0,255,0), nk_rgb(0,150,0), 32, -1.0f, 1.0f);
                for(id = 0, i = 0; i < 32; ++i)
                {
                    nk_chart_push_slot(ctx, (float)fabs(sin(id)), 0);
                    nk_chart_push_slot(ctx, (float)cos(id), 1);
                    nk_chart_push_slot(ctx, (float)sin(id), 2);
                    id += step;
                }
            }
            nk_chart_end(ctx);
        }
        else if(current_tab == 2)
        {
            nk_layout_row_static(ctx, 40, 150, 10);
            int new_theme;
            nk_label(ctx, "Temă de culori:", NK_TEXT_LEFT);
            new_theme = nk_combo(ctx, themes, NK_LEN(themes), current_theme, 35, nk_vec2(260, 200));
            if(new_theme != current_theme)
            {
                current_theme = new_theme;
                set_style(ctx, current_theme);
                live_config.color_theme = current_theme;
                save_config(live_config);
            }
            
        }
         
        nk_end(ctx);
    }
    nk_end(ctx);

    if(nk_window_is_hidden(ctx, "Panou de Control"))
    {
        log_info("Closing Main Window");
        is_main_window_exit = true; // triggers mainloop breaking (Do NOT call exit functions here)
    }
}

#endif