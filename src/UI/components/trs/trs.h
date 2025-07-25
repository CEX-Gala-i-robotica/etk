/*
TRS - Translation string
A language support component using cJSON for defining custom languages
*/


#include <stdbool.h>


#ifndef TRS_H
#define TRS_H


//#define TRS_EXIT_ERROR


typedef struct
{
    char *author;
    char *lang_name;
    char *version;
}trs_info;

typedef struct
{
    bool allow_sample_gen;
}trs_features;



void trs_set_features(trs_features settings);

// Get basic information about a translation
trs_info trs_get_translation_info(const char *fname);

// Load and store the keys and translated strings into memory
void trs_set_translation(const char *fname);

// Get a translated string from the current translation set
char *trs_get(const char *key_str);

// Get a translated string from the current translation set
void trs_gen_sample_strings(trs_info ti, const char *fname);

// Get a translated string from the current translation set
void trs_free();

// Free the memory used for getting language information
void trs_free_info(trs_info ti);





#endif