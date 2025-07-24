/*
TRS - Translation string
A language support component using cJSON for defining custom languages
*/


#ifndef TRS_H
#define TRS_H


//#define TRS_EXIT_ON_UNSET_LANG


typedef struct
{
    char *author;
    char *name;
    char *version;
}trs_info;


// Get basic information about a translation
trs_info trs_get_translation_info(const char *fname);

// Load and store the keys and translated strings into memory
void trs_set_translation(const char *fname);

// Get a translated string from the current translation set
char *trs_get(const char *key_str);

// Get a translated string from the current translation set
void trs_gen_sample_strings();

// Get a translated string from the current translation set
void trs_free();



#endif