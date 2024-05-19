#ifdef _WIN32
    #error "Windows not supported!"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bible.h"
#include "main.h"

static int fsize(FILE *fp){
    int prev=ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int sz=ftell(fp);
    fseek(fp,prev,SEEK_SET); //go back to where we were
    return sz;
}

#ifdef __APPLE__
    const char* paths[] = {".", "/usr/local/share/bible-cli"};
#else
    const char* paths[] = {".", "/usr/share/bible-cli"};
#endif

#define PATHS_AMOUNT 2

#define HOME getenv("HOME")

static FILE* get_file(const char* folder) {
    for (unsigned i = 0; i <= PATHS_AMOUNT; i++) {
        char path[MAX_PATH_SIZE];
        if (i < PATHS_AMOUNT)
            snprintf(path, MAX_PATH_SIZE, "%s/%s", paths[i], folder);
        else
            snprintf(path, MAX_PATH_SIZE, "%s/bible-cli/%s", HOME, folder);

        FILE* file = fopen(path, "r");
        if (file != NULL) {
            return file;
        }
    }
    return NULL;
}

cJSON* get_bible(const char* version, const char* book) {
    char path[MAX_PATH_SIZE];
    snprintf(path, MAX_PATH_SIZE, "%s/%s/%s.json", BIBLE_PATH, version, book);

    FILE* file = get_file(path);

    const int file_size = fsize(file);

    char buffer[file_size];
    fread(buffer, 1, file_size, file);

    return cJSON_Parse(buffer);
}
