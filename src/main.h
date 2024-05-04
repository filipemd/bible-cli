#ifndef MAIN_H
#define MAIN_H

#define MAX_PATH_SIZE 64
#define BIBLE_PATH "bible-json"

#ifdef _WIN32
#define PATH_SEPARATOR  "\\"
#else
#define PATH_SEPARATOR  "/"
#endif

#define SEP PATH_SEPARATOR

int index_string(const char *strings[], int size, const char *target, int jump);

#endif