#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <cJSON/cJSON.h>
#include <log_c/log.h>



#include "trs.h"






static trs_features recv_settings;

char ** trs_current_strings = NULL; // Sotre the translated strings
char ** trs_current_keys = NULL;    // Store the json keys after parsing
char ** trs_runtime_strings = NULL; // Store the strings collected at runtime trough trs_get()
bool is_translation_set;
int strings_count = 0;
int strings_count_runtime = 0;





/* - - - - Internal Functions - - - - */

int string_exists(const char *s)
{
    for(int i = 0; i < strings_count_runtime; i++)
    {
        if (trs_runtime_strings[i] && trs_runtime_strings[i][0] && strcmp(trs_runtime_strings[i], s) == 0)
            return 1;
    }
    return 0;
}

void add_runtime_strings(const char * s)
{
    if(string_exists(s))
    {
         return;
    }
    else
    {
        trs_runtime_strings = realloc(trs_runtime_strings, sizeof(char **) * (strings_count_runtime + 1));
        trs_runtime_strings[strings_count_runtime] = malloc(sizeof(char *) * 2);
        trs_runtime_strings[strings_count_runtime] = strdup(s);
        strings_count_runtime++;
    }
}



void trs_set_features(trs_features settings)
{
    recv_settings = settings;
}

void trs_set_translation(const char *fname)
{
    FILE * trs_lang = fopen(fname, "r");
    
    if(trs_lang == NULL)
        log_error("Failed to open translation file");
    else
    {
        // Read the file contents and populate the in_trs string
        fseek(trs_lang, 0, SEEK_END);
        long len = ftell(trs_lang);
        rewind(trs_lang);
        
        char *in_trs = (char *)malloc(len + 1);
        fread(in_trs, 1, len, trs_lang);
        in_trs[len] = '\0';
        fclose(trs_lang);
        
        cJSON *root = cJSON_Parse(in_trs); // Start parsing the json string
            
        if(!root)
        {
            free(in_trs);
            log_error("Error before %s", cJSON_GetErrorPtr());
#ifdef TRS_EXIT_ERROR
            exit(1);
#endif
        }
        else
        {
            cJSON *strings = cJSON_GetObjectItem(root, "strings");
            if(!cJSON_IsObject(strings))
            {
                log_error("\"strings\" is not an object\n");
                cJSON_Delete(root);
#ifdef TRS_EXIT_ERROR
                exit(1);
#endif
            }
            
            // Count all the available strings inside the "strings" object
            cJSON *item = NULL;
            cJSON_ArrayForEach(item, strings)
            {
                if(cJSON_IsString(item))
                    strings_count++;
            }
            
            // Memory allicatiob for storing the key names
            trs_current_keys = malloc(sizeof(char *) * strings_count);
            if(!trs_current_keys)
            {
                log_error("Failed to allocate memory for keys\n");
                cJSON_Delete(root);
#ifdef TRS_EXIT_ERROR
                exit(1);
#endif
            }
            
            // Memory allicatiob for storing the string names (aka translated strings)
            trs_current_strings = malloc(sizeof(char *) * strings_count);
            if(!trs_current_strings)
            {
                log_error("Failed to allocate memory for strings\n");
                cJSON_Delete(root);
#ifdef TRS_EXIT_ERROR
                exit(1);
#endif
            }
            
            // Assign each key and string to the arrays
            int i = 0;
            cJSON_ArrayForEach(item, strings)
            {
                if(cJSON_IsString(item))
                {
                    trs_current_strings[i] = strdup(item->valuestring);  // or use malloc + strcpy
                    trs_current_keys[i] = strdup(item->string);
                    i++;
                }
            }
            
            cJSON_Delete(root);
            
            is_translation_set = true;
        }
    }
}

// Memory safe so it can be used in imediate mode GUIs too
char *trs_get(const char *key_str)
{
    if(recv_settings.allow_sample_gen)
        add_runtime_strings(key_str);
    
    
    for(int i = 0; i < strings_count; i++)
    {
        if(strcmp(trs_current_keys[i], key_str) == 0)
            return trs_current_strings[i];  // found match 
    }
    
    return (char *)key_str;
}

void trs_gen_sample_strings(trs_info ti, const char *fname)
{
    if(!recv_settings.allow_sample_gen)
        log_error("Sample generation is not allowed. Please set \"trs_features >> allow_sample_gen = true\"");
    
    else
    {
        cJSON *root = cJSON_CreateObject();
        cJSON_AddStringToObject(root, "Name", ti.lang_name);
        cJSON_AddStringToObject(root, "Author", ti.author);
        cJSON_AddStringToObject(root, "Version", ti.version);
        
        cJSON *trs_strings = cJSON_CreateObject();
        
        for(int i = 0; i < strings_count_runtime; i++)
            cJSON_AddStringToObject(trs_strings, trs_runtime_strings[i], " - ");
        
        
        cJSON_AddItemToObject(root, "strings", trs_strings);
        char *json_str = cJSON_Print(root);
        
        FILE *f = fopen(fname, "w");
        if (f)
        {
            fputs(json_str, f);
            fclose(f);
        }
        else
            log_error("Failed to write language pack sample !!!");
    
        // Cleanup
        free(json_str);
        cJSON_Delete(root);
    }
}

trs_info trs_get_translation_info(const char *fname)
{
    trs_info lang_info;
    FILE * trs_lang = fopen(fname, "r");
    
    if(trs_lang == NULL)
    {
        lang_info.lang_name = NULL;
        lang_info.author = NULL;
        lang_info.version = NULL;
        log_error("Failed to open translation file");
    }
    else
    {
        // Read the file contents and populate the in_trs string
        fseek(trs_lang, 0, SEEK_END);
        long len = ftell(trs_lang);
        rewind(trs_lang);
        
        char *in_trs = (char *)malloc(len + 1);
        fread(in_trs, 1, len, trs_lang);
        in_trs[len] = '\0';
        fclose(trs_lang);
        
        cJSON *root = cJSON_Parse(in_trs); // Start parsing the json string
        
        const cJSON *trs_lang_name = cJSON_GetObjectItemCaseSensitive(root, "Name");
        const cJSON *trs_lang_author = cJSON_GetObjectItemCaseSensitive(root, "Author");
        const cJSON *trs_lang_version = cJSON_GetObjectItemCaseSensitive(root, "Version");
        
        // Initialize struct members with the parsed values
        if(cJSON_IsString(trs_lang_name))
            lang_info.lang_name = strdup(trs_lang_name->valuestring);
        
        if(cJSON_IsString(trs_lang_author))
            lang_info.author = strdup(trs_lang_author->valuestring);
        
        if(cJSON_IsString(trs_lang_version))
            lang_info.version = strdup(trs_lang_version->valuestring);
        
        
        cJSON_Delete(root);
        free(in_trs);
    }
    
    return lang_info;
}

void trs_free()
{
    // Free the translated strings array
    for(int j = 0; j < strings_count; j++)
        free(trs_current_strings[j]);
    
    free(trs_current_strings);
    
    // Free the keys array
    for(int j = 0; j < strings_count; j++)
        free(trs_current_keys[j]);
    
    free(trs_current_keys);
    
    if(recv_settings.allow_sample_gen)
    {
        for(int j = 0; j < strings_count_runtime; j++)
            free(trs_runtime_strings[j]);
        
        free(trs_runtime_strings);
        trs_runtime_strings = NULL;
        strings_count_runtime = 0;
    }
}

void trs_free_info(trs_info ti)
{
    free(ti.lang_name);
    free(ti.author);
    free(ti.version);
}