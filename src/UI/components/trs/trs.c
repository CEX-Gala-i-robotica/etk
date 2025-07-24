#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <cJSON/cJSON.h>
#include <log_c/log.h>



#include "trs.h"



/*
Todo:
- Implement trs_get_translation_info()
- Implement trs_gen_sample_strings()
*/



char ** trs_current_strings = NULL;
char ** trs_current_keys = NULL;
bool is_translation_set;
int strings_count = 0;



void trs_set_translation(const char *fname)
{
    FILE * trs_lang = fopen(fname, "r");
    
    if(trs_lang == NULL)
    {
        fclose(trs_lang);
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
            
        if(!root)
        {
            free(in_trs);
            log_error("Error before %s", cJSON_GetErrorPtr());
        }
        else
        {
            cJSON *strings = cJSON_GetObjectItem(root, "strings");
            if(!cJSON_IsObject(strings))
            {
                log_error("\"strings\" is not an object\n");
                cJSON_Delete(root);
            }
            
            // Count all the available strings inside the "strings" object
            cJSON *item = NULL;
            cJSON_ArrayForEach(item, strings)
            {
                if(cJSON_IsString(item))
                {
                    //printf("  %s: %s\n", item->string, item->valuestring);
                    strings_count++;
                }
            }
            
            // Memory allicatiob for storing the key names
            trs_current_keys = malloc(sizeof(char *) * strings_count);
            if(!trs_current_keys)
            {
                log_error("Failed to allocate memory for keys\n");
                cJSON_Delete(root);
            }
            
            // Memory allicatiob for storing the string names (aka translated strings)
            trs_current_strings = malloc(sizeof(char *) * strings_count);
            if(!trs_current_strings)
            {
                log_error("Failed to allocate memory for strings\n");
                cJSON_Delete(root);
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
    for(int i = 0; i < strings_count; i++)
    {
        if(strcmp(trs_current_keys[i], key_str) == 0)
        {
            return trs_current_strings[i];  // found match
        }
    }
    
    return (char *)key_str;
}

void trs_free()
{
  
    
    // Free the translated strings array
    for(int j = 0; j < strings_count; j++)
    {
        free(trs_current_strings[j]);
    }
    free(trs_current_strings);
    
    // Free the keys array
    for(int j = 0; j < strings_count; j++)
    {
        free(trs_current_keys[j]);
    }
    free(trs_current_keys);
}