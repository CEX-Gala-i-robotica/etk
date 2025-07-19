#ifndef CONFIG_UTILS_H
#define CONFIG_UTILS_H


#include <stdbool.h>


#define MAX_PATH 450
#define CFG_FILE_PATH ".config/etk/settings.json"





typedef struct
{
    bool loop_mode;
    bool always_show_plots;
    bool autosave_csv;
    bool logs_2_file;
    bool internal_buzzer;
    bool show_power_status;
    bool save_ui_state;
    bool always_clear_gpio_on_exit;
    bool virtual_osc;
}Configuration;



extern Configuration live_config;
extern Configuration parsed_config;

int isFileExistsAccess(const char *path);
int isDirectoryExists(const char *path);
int createDir(const char *path);

void configuration_setup();
Configuration load_config();
void save_config(Configuration cfg);

#endif