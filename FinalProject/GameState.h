//
// Created by Dror on 2017-08-19.
//

/*
 * While GameBoard only holds a board position,
 * this also holds other game settings such as history, difficulty, game mode etc.
 */


#ifndef CHESS1_GAMESTATE_H
#define CHESS1_GAMESTATE_H

#include "GameBoard.h"

typedef struct chess_gamestate{
    GameBoard* gameBoard;
    char difficulty; // 1-5
    bool isPlayerWhite;
    bool mode; // false is 1
    // TODO: history
} GameState;

GameState* GameStateCreate();

#endif //CHESS1_GAMESTATE_H
