#include "MainAux.h"

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "-g") == 0) startGUIMode();
    else startConsoleMode();

    return 0;
 }
