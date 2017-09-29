//
// Created by Dror on 2017-08-19.
//

/*
 * While GameBoard only holds a board position,
 * this also holds other game settings such as history, difficulty, game mode etc.
 */


#ifndef CHESS1_GAMESTATE_H
#define CHESS1_GAMESTATE_H

#define MAX_UNDO 3

#include "GameBoard.h"
#include "Moves.h"

// contains everything about a game, including board, game settings and history
typedef struct chess_gamestate{
    GameBoard* gameBoard;
    int current_move; // TODO: newly added, make sure we deal with this everywhere
    char difficulty; // 1-5
    char mode; // 1 or 2
    bool isPlayerWhite;
    HistoryMove* history[MAX_UNDO*2]; // each undo also undoes opponent
    // TODO: do i need to allocate the above explicitly?
} GameState;

GameState* GameStateCreate(char difficulty, bool isPlayerWhite, char mode);
void GameStateDestroy(GameState* game);

bool GameStatePerformMove(GameState* game, char y1, char x1, char y2, char x2);

//bool GameStateUndoMove(GameState* game);

HistoryMove* GameStateGetLastMove(GameState* game);

void GameStateUndoHistoryMove(GameState* game);


#endif //CHESS1_GAMESTATE_H
