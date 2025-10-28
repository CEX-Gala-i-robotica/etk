#ifndef TTP229_H
#define TTP229_H


#include <stdint.h>



void wait_for_key_release();
void wait_for_key_event();
void Setup_TTP229();
uint16_t TTP229_GetPressed();
void print_keys(uint16_t keys);
#endif