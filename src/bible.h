#ifndef BIBLE_H
#define BIBLE_H

#include <stdint.h>
#include "cJSON.h"

#define MAX_PATH_SIZE 64
#define BIBLE_PATH "bible-json"

const cJSON* get_bible(const char* version, const char* book);

#endif