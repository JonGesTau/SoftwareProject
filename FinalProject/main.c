#include <stdio.h>
#include <memory.h>
#include "ChessParser.h"
#include "MainAux.h"

int main(int argc, char *argv[]) {
    if (argv[1] == "-g") startGUIMode();
    else startConsoleMode();

    return 0;
 }