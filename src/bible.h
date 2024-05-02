#ifndef BIBLE_H
#define BIBLE_H

#include <stdint.h>
#include "cJSON.h"

const cJSON* get_bible(const char* version, const char* book);

#endif