#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "../tests.h"
#include "../config_utils.h"

#include <qrencode.h>







bool is_main_window_exit = false;
static int current_tab = 0;

static int selected_component = CT_ARDUINO_UNO;
int is_selected;

int group_heights = 660;
int component_widget_group = 880;

static nk_bool cb_loop_test;
static nk_bool cb_manual_ctrl;



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
    is_selected = (selected_component == id);
    if(nk_selectable_label(ctx, label, NK_TEXT_LEFT, &is_selected))
    {
        selected_component = id;
    }
}

void start_test()
{
    log_info("Start testing ...");
    // Do testing stuff here
}

void stop_loop_test()
{
    log_info("Stop loop testing...");
    
    // Stop the loop test if loop_mode is true
}




// The UI ain't good enough ;(
void render_main_window(struct nk_context *ctx)
{
    
    
    if(nk_begin(ctx, "Panou de Control", nk_rect(48, 80, 1400, 810), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_CLOSABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
    {
        nk_layout_row_dynamic(ctx, 30, 3);
            
        tab_button(ctx, "Teste", 0, &current_tab);
        tab_button(ctx, "Date în timp real", 1, &current_tab);
        tab_button(ctx, "Setări", 2, &current_tab);
        // ----------------------------------
        nk_layout_row_dynamic(ctx, 10, 1);
        
        // Handle tab selection
        if(current_tab == 0)
        {
            nk_layout_space_begin(ctx, NK_STATIC, group_heights, 2);
            nk_layout_space_push(ctx, nk_rect(0, 0, 450, group_heights));
            if(nk_group_begin(ctx, "Component Group", NK_WINDOW_BORDER))
            {
                // Add all the component items under its own category
                if(nk_tree_push(ctx, NK_TREE_NODE, "Microcontrolere și platforme ", NK_MINIMIZED))
                {
                    
                    nk_layout_row_push(ctx, 900);
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
                
                if(nk_tree_push(ctx, NK_TREE_NODE, "Alimentare și control tensiune / voltaj", NK_MINIMIZED))
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
            nk_layout_space_push(ctx, nk_rect(470, 0, 908, group_heights));
            if(nk_group_begin(ctx, "Component widgets", NK_WINDOW_BORDER))
            {
                // Wooohh so many pages and those are just few of the common components
                if(selected_component == CT_ARDUINO_UNO)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 1", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_ARDUINO_NANO)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 2", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_ARDUINO_MEGA)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 3", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_ARDUINO_GIGA)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 4", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_LCD_I2C)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 5", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_LCD)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 6", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_OLED)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 7", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_TFT)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 8", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_ULTRASONIC_HC06)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 9", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_INFRARED)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 10", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_DHT)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 11", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_GAS_SENSOR)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 12", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_SMOKE_DETECTOR)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 13", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_WATER_LEVEL)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 14", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_SOIL_MOISTURE)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 15", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_SPEED_SENSOR)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 16", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_MPU6050)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 17", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_MICROPHONE)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 18", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_SERVO)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 19", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_STEPPER_MOTOR_ULN2003)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 20", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_A4988_DRIVER)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 21", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_H_BRIDGE_L298N)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 22", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_PCA9685)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 23", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_POTENTIOMETER)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 24", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_JOYSTICK_X2)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 25", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_FLOW_METER)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 26", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_PHOTORESISTOR)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 27", NK_TEXT_LEFT);
                }
                else if(selected_component == CT_HALL_SENSOR)
                {
                    nk_layout_row_static(ctx, 30, component_widget_group, 1);
                    nk_label(ctx, "Page 28", NK_TEXT_LEFT);
                }
                nk_group_end(ctx);
            }
            
            float widths[] = {32, 32, 150, 180}; // Set custom widths for each column inside the row so everything fits nicely
            nk_layout_row(ctx, NK_STATIC, 32, 4, widths);
            if(nk_button_symbol(ctx, NK_SYMBOL_TRIANGLE_RIGHT))
                start_test();
                
            if(!cb_loop_test)
            {
                nk_widget_disable_begin(ctx); // Disable the stop test button if loop_mode is false because the automatic test runs for few seconds / minutes (Depending on the component being tested)
            }
            if(nk_button_symbol(ctx, NK_SYMBOL_RECT_SOLID))
                stop_loop_test();
                
            nk_widget_disable_end(ctx);
            
            nk_checkbox_label(ctx, "Continuitate", &cb_loop_test);
            nk_checkbox_label(ctx, "Control Manual", &cb_manual_ctrl);
            
            live_config.loop_mode = cb_loop_test;
            live_config.manual_ctrl = cb_manual_ctrl;
        }
        else if(current_tab == 1) // Handle tab selection
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
        else if(current_tab == 2) // Handle tab selection
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


void draw_qr_code(struct nk_command_buffer *canvas, int x, int y, int size, const char *text) {
    QRcode *qrcode = QRcode_encodeString(text, 0, QR_ECLEVEL_L, QR_MODE_8, 1);
    if (!qrcode) return;

    int qr_width = qrcode->width;
    int pixel_size = size / qr_width;
    unsigned char *data = qrcode->data;

    for (int row = 0; row < qr_width; ++row) {
        for (int col = 0; col < qr_width; ++col) {
            int offset = row * qr_width + col;
            if (data[offset] & 0x01) { // black module
                nk_fill_rect(canvas,
                    nk_rect(x + col * pixel_size, y + row * pixel_size,
                            pixel_size, pixel_size),
                    0.0f, nk_rgb(0, 0, 0));
            }
        }
    }

    QRcode_free(qrcode);
}

void nk_qr_demo(struct nk_context *ctx)
{
    if(nk_begin(ctx, "QR Demo", nk_rect(48, 80, 500, 500), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_CLOSABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
    {
        nk_layout_row_dynamic(ctx, 30, 1);
            static char text[256] = "https://github.com/CEX-Gala-i-robotica/etk/tree/nuklear-gui";
            nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, text, sizeof(text), nk_filter_default);
        
            nk_layout_row_dynamic(ctx, 30, 1);
            if (nk_button_label(ctx, "Generate QR")) {
                // You could do something here if needed
            }
        
            // Draw custom QR code inside canvas region
            struct nk_command_buffer *canvas = nk_window_get_canvas(ctx);
        
            int qr_x = 100;
            int qr_y = 100;
            int qr_size = 200;
        
            draw_qr_code(canvas, qr_x, qr_y, qr_size, text);
    }
    nk_end(ctx);
}

#endif