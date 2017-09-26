//
// Created by Dror on 2017-08-19.
//

#ifndef CHESS1_MINIMAX_H
#define CHESS1_MINIMAX_H

#include <limits.h>
#include <stdbool.h>
#include "GameBoard.h"
#include "Moves.h"

/*
 * Use this function to select a move:
 *   game - a GameBoard object
 *   depth and maxDepth should both be equal to the depth that should be read.
 *     (depth = 1 means just select the best immediate move)
 *   isMax - true if searching move for white, otherwise false
 *   parentBest - doesn't matter what you put here, just put 0.
 */

ScoredMove* miniMaxGetBestMove(GameBoard* game, char depth, char maxDepth, bool isMax, int parentBest);

// given a board (a node in the minimax tree), returns a naive evaluation
// positive is good for white
int miniMaxBoardScore(GameBoard* game);

#endif //CHESS1_MINIMAX_H
