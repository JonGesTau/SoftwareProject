//
// Created by Dror on 2017-08-26.
//

#include "consoleUITest.h"

int consoleTest(){
    GameBoard* game = gameBoardCreate();
    gameBoardSetup(game, true);

    consoleUIPrintBoard(game);

    gameBoardDestroy(game);
    return 0;
}