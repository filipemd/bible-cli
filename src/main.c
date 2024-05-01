#include <stdio.h>
#include <stdlib.h>

#include "bible.h"

int main(int argc, char* argv[]) {
    if (argc > 3) {
        const cJSON* bible = get_bible(argv[1], argv[2]);

        const uint8_t chapter_number = atoi(argv[3])-1;
        const uint8_t bookSize = cJSON_GetArraySize(bible);
        if (chapter_number >= bookSize) {
            printf("The amount of chapters in the book is %d.\n", bookSize);
            return -1;
        }
        const cJSON* chapter = cJSON_GetArrayItem(bible, chapter_number);
        if (argc == 5) {
            const uint8_t verse_number = atoi(argv[4])-1;
            const uint8_t chapterSize = cJSON_GetArraySize(chapter);
            if (verse_number >= chapterSize) {
                printf("The amount of verses in the chapter is %d.\n", chapterSize);
                return -1;
            }
            printf("%s chapter %d verse %d version: %s.\n\n", argv[2], chapter_number+1, verse_number+1, argv[1]);
            printf("%s\n", cJSON_GetArrayItem(chapter, verse_number)->valuestring);
        } else {
            printf("%s chapter %d version: %s.\n\n", argv[2], chapter_number+1, argv[1]);

            uint8_t verse_number = 1;
            const cJSON* verse = NULL;
            cJSON_ArrayForEach(verse, chapter) {
                printf("%d %s\n", verse_number, verse->valuestring);
                verse_number++;
            }
        }
    } else {
        printf("Usage: \n");
        printf("bible <version> <book> <chapter> <verse>\n");
    }

    return 0;
}