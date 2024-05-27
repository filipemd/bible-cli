#ifdef _WIN32
    #error "Windows not supported!"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bible.h"
#include "main.h"

static int fsize(FILE *fp){
    int prev = ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    fseek(fp, prev, SEEK_SET); // Voltar à posição original
    return sz;
}

#ifdef __APPLE__
    const char* paths[] = {".", "/usr/local/share/bible-cli"};
    #define PATHS_AMOUNT 2
#else
    const char* paths[] = {".", "/usr/share/bible-cli"};
    #define PATHS_AMOUNT 1
#endif

#define HOME getenv("HOME")

static char* get_file(const char* folder) {
    char path[MAX_PATH_SIZE];
    for (unsigned i = 0; i < PATHS_AMOUNT; i++) {            
        snprintf(path, MAX_PATH_SIZE, "%s/%s", paths[i], folder);

        FILE* file = fopen(path, "r");
        if (file != NULL) {
            return path;
        }
    }

    snprintf(path, MAX_PATH_SIZE, "%s/bible-cli/%s", HOME, folder);

    return path;
}

static cJSON* file_to_json(const char* path) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        return NULL; // Verificar se o arquivo foi aberto corretamente
    }

    const int file_size = fsize(file);
    char buffer[file_size + 1]; // Alocar dinamicamente o buffer

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0'; // Garantir que o buffer esteja null-terminated
    fclose(file); // Fechar o arquivo após a leitura

    cJSON* json = cJSON_Parse(buffer);

    return json;
}

cJSON* get_bible(const char* version, const char* book) {
    char path[MAX_PATH_SIZE];
    snprintf(path, MAX_PATH_SIZE, "%s/%s/%s.json", BIBLE_PATH, version, book);

    return file_to_json(get_file(path));
}

void bible_save(unsigned version, uint8_t book, uint8_t chapter) {
    cJSON* json = cJSON_CreateObject();
    
    cJSON_AddNumberToObject(json, "version", version);
    cJSON_AddNumberToObject(json, "book", book);
    cJSON_AddNumberToObject(json, "chapter", chapter);

    char *json_str = cJSON_Print(json);

    char path[MAX_PATH_SIZE];
    snprintf(path, MAX_PATH_SIZE, "%s/.bible/history.json", HOME);
    FILE *fp = fopen(path, "w");
    
    if (fp != NULL) {
        fputs(json_str, fp);
        fclose(fp);
    }

    free(json_str);
    cJSON_Delete(json);
}

cJSON* bible_get_save(void) {
    char path[MAX_PATH_SIZE];
    snprintf(path, MAX_PATH_SIZE, "%s/.bible/history.json", HOME);

    return file_to_json(path);
}
