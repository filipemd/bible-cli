#include <stdio.h>
#include <string.h>

#include "bible.h"

#define MAX_PATH_SIZE 64
#define BIBLE_PATH "bible-json"

#ifdef _WIN32
#define PATH_SEPARATOR  "\\"
#else
#define PATH_SEPARATOR  "/"
#endif

static int fsize(FILE *fp){
    int prev=ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int sz=ftell(fp);
    fseek(fp,prev,SEEK_SET); //go back to where we were
    return sz;
}

const cJSON* get_bible(const char* version, const char* book) {
    char path[MAX_PATH_SIZE];
    snprintf(path, MAX_PATH_SIZE, "%s%s%s%s%s.json", BIBLE_PATH, PATH_SEPARATOR, version, PATH_SEPARATOR, book);

    FILE* file = fopen(path, "r");
    if (file == NULL) {
        printf("Version or book doesn't exists!.\n");
        return NULL;
    }
    const int file_size = fsize(file);

    char buffer[file_size];
    fread(buffer, 1, file_size, file);

    return cJSON_Parse(buffer);
}