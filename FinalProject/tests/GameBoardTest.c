//
// Created by Dror on 2017-08-26.
//

#include "GameBoardTest.h"

int tryMove(GameBoard* game, char y1, char x1, char y2, char x2){
    if(!gameBoardIsLegalMove(game, y1, x1, y2, x2)){
        printf("Illegal move!\n");
        return -1;
    }
    gameBoardPerformMove(game, y1, x1, y2, x2);
    printf("\n");
    consoleUIPrintBoard(game);
    return 0;
}

int isLegalTest1(){
    GameBoard* game = gameBoardCreate();
    gameBoardSetup(game, true);

    consoleUIPrintBoard(game);

    tryMove(game, 1, 0, 3, 0);
    //tryMove(game, 3, 0, 1, 0);
    tryMove(game, 0, 0, 2, 0);
    tryMove(game, 6, 3, 4, 3);
    tryMove(game, 2, 0, 2, 0); // bad
    tryMove(game, 2, 0, 3, 1); // bad
    tryMove(game, 2, 0, 2, 3);
    tryMove(game, 2, 3, 1, 3); // bad
    tryMove(game, 2, 3, 4, 3);
    // capturing with pawn
    tryMove(game, 3, 0, 4, 0);
    tryMove(game, 4, 0, 5, 0);
    tryMove(game, 5, 0, 6, 0); // bad
    tryMove(game, 5, 0, 6, 1);
    tryMove(game, 6, 1, 7, 1); // bad
    tryMove(game, 6, 1, 7, 0);



    gameBoardDestroy(game);
    return 0;
}

int isLegalTest2(){
    // knights and kings
    GameBoard* game = gameBoardCreate();
    gameBoardSetup(game, true);

    consoleUIPrintBoard(game);

    tryMove(game, 7, 1, 7, 1); // bad
    tryMove(game, 7, 1, 7, 2); // bad
    tryMove(game, 7, 1, 6, 3); // bad
    tryMove(game, 7, 1, 5, 2);
    tryMove(game, 5, 2, 4, 4);
    tryMove(game, 4, 4, 3, 2);
    tryMove(game, 4, 4, 4, 6); // bad
    tryMove(game, 3, 2, 1, 3);

    // try the king
    tryMove(game, 0, 4, 0, 3); // bad
    tryMove(game, 0, 4, 1, 4); // bad
    tryMove(game, 0, 4, 1, 5); // bad
    tryMove(game, 0, 4, 1, 3);
    tryMove(game, 1, 3, 1, 4); // bad
    tryMove(game, 1, 3, 2, 3);
    tryMove(game, 2, 3, 2, 2);
    tryMove(game, 2, 2, 3, 1);

    gameBoardDestroy(game);
    return 0;
}

int isLegalTest3(){
    // bishop & queen
    GameBoard* game = gameBoardCreate();
    gameBoardSetup(game, true);

    consoleUIPrintBoard(game);

    tryMove(game, 6, 6, 5, 6);
    tryMove(game, 7, 5, 5, 7);
    tryMove(game, 5, 7, 6, 6);
    tryMove(game, 6, 6, 4, 4);
    tryMove(game, 4, 4, 6, 2); // bad
    tryMove(game, 4, 4, 3, 4); // bad
    tryMove(game, 4, 4, 1, 2); // bad
    tryMove(game, 4, 4, 1, 1);
    tryMove(game, 1, 1, 0, 2);
    tryMove(game, 0, 2, 0, 3); // bad
    tryMove(game, 0, 2, 2, 4); // bad
    tryMove(game, 0, 2, 1, 3);

    // now queen
    tryMove(game, 0, 3, 0, 4); // bad
    tryMove(game, 0, 3, 2, 3); // bad
    tryMove(game, 0, 3, 2, 4); // bad
    tryMove(game, 0, 3, 1, 3);
    tryMove(game, 1, 3, 4, 0);
    tryMove(game, 4, 0, 4, 6);


    gameBoardDestroy(game);
    return 0;
}

int isThreatenedTest1(){
    GameBoard* game = gameBoardCreate();
    gameBoardSetup(game, true);

    consoleUIPrintBoard(game);

    printf("%d ", (int) gameBoardIsThreatened(game, 0, 0));
    tryMove(game, 6, 6, 5, 6);
    tryMove(game, 7, 5, 5, 7);
    printf("%d ", (int) gameBoardIsThreatened(game, 1, 3));
    printf("%d ", (int) gameBoardIsThreatened(game, 1, 4));
    printf("%d ", (int) gameBoardIsThreatened(game, 0, 4));
    tryMove(game, 5, 7, 1, 3);
    printf("%d ", (int) gameBoardIsThreatened(game, 0, 4));


    gameBoardDestroy(game);
    return 0;
}

int gameBoardTest(){
    isThreatenedTest1();
    return 0;
}