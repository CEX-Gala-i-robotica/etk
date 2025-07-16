#include <cJSON/cJSON.h>
#include <log_c/log.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>




#include "config_utils.h"


int isFileExistsAccess(const char *path)
{
    if(access(path, F_OK) == -1)
        return 0;
    
    return 1;
}

int isDirectoryExists(const char *path)
{
    struct stat stats;
    
    stat(path, &stats);
    
    // Check for file existence
    if(S_ISDIR(stats.st_mode))
        return 1;

    return 0;
}

int createDir(const char *path)
{
    int check;
    
    check = mkdir(path,0777);
    
    // check if directory is created or not
    if (!check)
        log_info("Directory created | path: %s", path);
    else
    {
        log_error("Failed to create directory !!! path: %s", path);
    }
    return check;
}


void configuration_setup()
{
    char filepath[MAX_PATH];
    
    
    snprintf(filepath, MAX_PATH, "%s/%s", getenv("HOME"), ".config/etk");
    if(!isDirectoryExists(filepath))
    {
        log_warn("etk dir not found in .config");
        createDir(filepath);
    }
    else
    {
        log_info("etk dir found in .config");
    }
}


Configuration load_config()
{
    Configuration out_cfg;
    char filepath[MAX_PATH];
    
    
    snprintf(filepath, MAX_PATH, "%s/%s", getenv("HOME"), CFG_FILE_PATH);
    
    FILE * in_file = fopen(filepath, "r");
      
    if(!in_file)
    {
        log_error("Failed to open '%s' !!!", filepath);
    }
    else
    {
        fseek(in_file, 0, SEEK_END);
        long len = ftell(in_file);
        rewind(in_file);
        
        char *in_conf_str = (char *)malloc(len + 1);
        fread(in_conf_str, 1, len, in_file);
        in_conf_str[len] = '\0';
        fclose(in_file);
            
            
        cJSON *root = cJSON_Parse(in_conf_str);
            
        if(!root)
        {
            log_error("Error before %s", cJSON_GetErrorPtr());
            free(in_conf_str);
        }
        else
        {
            const cJSON *cfg_loop_probe = cJSON_GetObjectItemCaseSensitive(root, "loopProbe");
            const cJSON *cfg_virtual_osc = cJSON_GetObjectItemCaseSensitive(root, "virtualOscilloscope");
            
            if(cJSON_IsBool(cfg_loop_probe))
            {
              out_cfg.loop_mode = cfg_loop_probe->valueint;
            }
            
            if(cJSON_IsBool(cfg_virtual_osc))
            {
              out_cfg.virtual_osc = cfg_virtual_osc->valueint;
            }
            
            cJSON_Delete(root);
            free(in_conf_str);
        }
    }
    return out_cfg;
}

void save_config(Configuration cfg)
{
    cJSON *root = cJSON_CreateObject();
    char filepath[MAX_PATH];
    
    cJSON_AddBoolToObject(root, "loopProbe", cfg.loop_mode);
    cJSON_AddBoolToObject(root, "virtualOscilloscope", cfg.virtual_osc);
    
    
    char *json_string = cJSON_Print(root);
    
    
    snprintf(filepath, MAX_PATH, "%s/%s", getenv("HOME"), CFG_FILE_PATH);
    
    FILE *out_file = fopen(filepath, "w");
      
    if(out_file)
    {
        fputs(json_string, out_file);
        puts(json_string);
        fclose(out_file);
    }
    else
        log_error("Failed to open '%s' for writing !!!", filepath);
    
    cJSON_free(json_string);
}