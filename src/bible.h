#ifndef BIBLE_H
#define BIBLE_H

#include <stdint.h>
#include "cJSON/cJSON.h"

cJSON* get_bible(const char* version, const char* book);

void bible_save(unsigned version, uint8_t book, uint8_t chapter);
cJSON* bible_get_save(void);

#endif
