//
// Created by Dror on 2017-08-26.
//

#ifndef CHESS1_GAMEBOARDTEST_H
#define CHESS1_GAMEBOARDTEST_H

#include <stdio.h>
#include "../consoleUI.h"

int tryMove(GameBoard* game, char y1, char x1, char y2, char x2);
int isLegalTest1();
int isLegalTest2();
int isLegalTest3();
int isThreatenedTest1();
int gameBoardTest();

#endif //CHESS1_GAMEBOARDTEST_H
