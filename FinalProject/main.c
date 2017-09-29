#include <stdio.h>
#include <memory.h>
#include "MainAux.h"
//#include "ChessParser.h"

int main(int argc, char *argv[]) {
    if (argv[1] == "-g") startGUIMode();
    else startConsoleMode();

    return 0;
 }