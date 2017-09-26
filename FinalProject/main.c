#include <stdio.h>
#include "MainAux.h"

int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "-g") == 0) startGUIMode();
    else startConsoleMode();

    return 0;
 }