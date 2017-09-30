//
// Created by Dror on 2017-08-18.
//

#ifndef CHESS1_CONSOLEUI_H
#define CHESS1_CONSOLEUI_H

#include <stdio.h>

#include "GameBoard.h"

#define consolePieceChar(p) (("_mbnrqk"[whichPiece(p)]) + (isBlack(p)?-32:0))

/**
 * Prints to the console the string representation of a GameBoard.
 * @param game - Pointer to the GameBoard* to be printed.
 */
void consoleUIPrintBoard(GameBoard* game);


#endif //CHESS1_CONSOLEUI_H
