#include <stdlib.h>
#include <string.h>

extern "C" {
#include "cli-main.h"
}
#include "gui-main.h"

int main(int argc, char* argv[]) {
    if (strcmp(argv[argc-1], "--cli") == 0)
        return cli_main(argc, argv);
    else
        return gui_main(argc, argv);
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
