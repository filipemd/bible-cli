#include <stdio.h>
#include <stdlib.h>

#include "main.h"

#include "bible.h"
#include "bible-lists.h"

static void show_versions() {
    printf("Versions: \n\n");
    for(unsigned i = 0; i < VERSIONS_AMOUNT*2; i+=2) {
        printf("%s\t%s\n", versions[i], versions[i+1]);
    }
}

static void show_books() {
    printf("\nBooks: \n\n");
    for(unsigned i = 0; i < BOOKS_AMOUNT*2; i+=2) {
        printf("%s\t%s\n", books[i], books[i+1]);
    }
}

int cli_main(int argc, char* argv[]) {
    if (argc > 3) {
        if (index_string(versions, VERSIONS_AMOUNT, argv[1], 2) == -1) {
            printf("Version does not exist!!\n\n");
            show_versions();
            return -1;
        }
        if (index_string(books, BOOKS_AMOUNT, argv[2], 2) == -1) {
            printf("Book does not exist!!\n\n");
            show_books();
            return -1;
        }
        cJSON* bible = get_bible(argv[1], argv[2]);
        if (!bible){
            return -1;
        }

        const uint8_t chapter_number = atoi(argv[3])-1;
        const uint8_t bookSize = cJSON_GetArraySize(bible);
        if (chapter_number >= bookSize) {
            printf("The amount of chapters in the book is %d.\n", bookSize);
            return -1;
        }
        cJSON* chapter = cJSON_GetArrayItem(bible, chapter_number);
        if (argc >= 5) {
            const uint8_t verse_number = atoi(argv[4])-1;
            const uint8_t chapterSize = cJSON_GetArraySize(chapter);
            if (verse_number >= chapterSize) {
                printf("The amount of verses in the chapter is %d.\n", chapterSize);
                return -1;
            }
            printf("%s chapter %d verse %d. Version: %s.\n\n", books[index_string(books, BOOKS_AMOUNT, argv[2], 2)+1], chapter_number+1, verse_number+1, versions[index_string(versions, VERSIONS_AMOUNT, argv[1], 2)+1]);
            printf("%s\n", cJSON_GetArrayItem(chapter, verse_number)->valuestring);
        } else {
            printf("%s chapter %d. Version: %s.\n\n", books[index_string(books, BOOKS_AMOUNT, argv[2], 2)+1], chapter_number+1, versions[index_string(versions, VERSIONS_AMOUNT, argv[1], 2)+1]);

            uint8_t verse_number = 1;
            cJSON* verse = NULL;
            cJSON_ArrayForEach(verse, chapter) {
                printf("%d %s\n", verse_number, verse->valuestring);
                verse_number++;
            }
        }
    } else {
        printf("Usage: \n");
        printf("bible <version> <book> <chapter> <verse>\n\n");

        show_versions();
        show_books();
    }

    return 0;
}