//
// Created by Dror on 2017-08-19.
//

#ifndef CHESS1_MINIMAX_H
#define CHESS1_MINIMAX_H

#include <limits.h>
#include <stdbool.h>
#include "GameBoard.h"
//int spMiniMaxNodeEvaluate(SPFiarGame* board, unsigned int depth, unsigned int maxDepth, bool sign){
int miniMaxGetBestMove(GameBoard* game, char depth, char maxDepth, bool isMax, int parentBest);
int miniMaxBoardScore(GameBoard* game);

#endif //CHESS1_MINIMAX_H
