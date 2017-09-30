//
// Created by Dror on 2017-08-19.
//

#ifndef CHESS1_MINIMAX_H
#define CHESS1_MINIMAX_H

#include <limits.h>
#include <stdbool.h>
#include "GameBoard.h"
#include "Moves.h"
#include "GameState.h"

/*
 * Use this function to select a move:
 *   game - a GameBoard object
 *   depth and maxDepth should both be equal to the depth that should be read.
 *     (depth = 1 means just select the best immediate move)
 *   isMax - true if searching move for white, otherwise false
 *   parentBest - doesn't matter what you put here, just put 0.
 */
/**
 * Recommends a move using the MiniMax algorithm. Should only be used in miniMaxGetComputerMove.
 * @param game - the board.
 * @param depth - the current depth of recursion.
 * @param maxDepth - the maximum depth of recursion.
 * @param isMax - true if looking for a best move for white, false otherwise.
 * @param parentBest - when depth != maxDepth, this holds the current best score for the parent node.
 *          otherwise, can hold any value.
 * @return a ScoreMove containing the best move found.
 */
ScoredMove* miniMaxGetBestMove(GameBoard* game, char depth, char maxDepth, bool isMax, int parentBest);

/**
 * Uses miniMaxGetBestMove to choose a move for the computer.
 * @param game
 * @return A Move object with the chosen move.
 */
Move* miniMaxGetComputerMove(GameState* game);

/**
 * Given a static board position, evaluates the material value using the given algorithm.
 * Positive values are good for white, negative for black. 0 means either tie or equal material.
 * @param game
 * @return The value of the position, positive is good for white, negative is good for black.
 */
int miniMaxBoardScore(GameBoard* game);

#endif //CHESS1_MINIMAX_H
