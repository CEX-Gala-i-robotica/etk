/*
TRS - Translation string
A language support component using cJSON for defining custom languages
*/


#ifndef TRS_H
#define TRS_H


//#define TRS_EXIT_ON_UNSET_LANG


// Load all available language packs (as .json files) with this file naming pattern "trs_<lang>.json"
char **trs_get_available_translations(const char *lang_pack_dir);
void trs_set_translation(const char *translation_name);
char trs_get(const char *str); // Get a translated string from the current translation set
char **trs_get_required(); // Get all string names that require translation



#endif