#include <stdlib.h>
#include <string.h>

extern "C" {
#include "cli-main.h"
}

#ifndef CLI
#include "gui/gui-main.h"
#endif

int main(int argc, char* argv[]) {
    #ifdef CLI
    return cli_main(argc, argv);
    #else

    if (strcmp(argv[argc-1], "--cli") == 0)
        return cli_main(argc-1, argv);
    else
        return gui_main(argc, argv);
    #endif
}

extern "C" int index_string(const char *strings[], int size, const char *target, int jump) {
    int i;
    for (i = 0; i < size*jump; i+=jump) {
        if (strcmp(strings[i], target) == 0) {
            return i;  // Encontrou a string, retorna o índice
        }
    }
    return -1;  // String não encontrada na lista
}
