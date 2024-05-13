#ifndef BIBLE_H
#define BIBLE_H

#include <stdint.h>
#include "cJSON/cJSON.h"

cJSON* get_bible(const char* version, const char* book);

#endif
