//
// Created by Dror on 2017-08-26.
//

#include <stdio.h>

#include "../xmlGame.h"

int xmlTest();
int xmlLoadTest1();

int xmlTest(){
    xmlLoadTest1();
}

int xmlSaveTest() {
    GameState* game = GameStateCreate(3, true, 1);

    xmlGameSaveGame(game, "tst1.xml");

    printf("printed successfully\n");

    // (("_mbnrqk"[whichPiece(p)]) + (isBlack(p)?-32:0))
    //printf("%d ", game->gameBoard->board[0][0]);
    //printf("%d ", whichPiece(game->gameBoard->board[0][0]));
    //printf("%c", "_mbnrqk"[4]-32);

    GameStateDestroy(game);

    return 0;
}

int xmlLoadTest1(){
    xmlGameLoadGame("loadtest.xml");
}
