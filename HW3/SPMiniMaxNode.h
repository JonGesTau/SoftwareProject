#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_

#define SP_MINI_MAX_NODE_PLAYER_VAL(p) (p == SP_FIAR_GAME_EMPTY_ENTRY ? 0 : (p == SP_FIAR_GAME_PLAYER_1_SYMBOL ? 1 : -1))
#define brd board->gameBoard


#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "SPFIARGame.h"

//Put all decleartions and constants here
/**
 * Evaluates a given board position according to the formula
 * specified in the project instructions.
 *
 * @board - The board position to evaluate.
 * @return
 * Returns an integer value expressing the evaluation of the board position.
 * Positive values are favorable for player 1.
 */
int spMiniMaxNodeScore(SPFiarGame* board);

/**
 * This function is part of the miniMax heuristic. It enumerates all
 * the possible next moves, and evaluates each one recursively.
 *
 * @board - The board position to evaluate.
 * @depth - The current depth of the miniMax evaluation.
 * @maxDepth - The maximum depth of evaluation.
 * @sign - True if it is player 1's turn, False otherwise.
 * @return
 * If depth is less than maxDepth, return the best evaluation given to any
 * of the possible continuations. The best evaluation is the maximum
 * score if sign is True, otherwise it is the minimum.
 * If depth is equal to maxDepth, return the move which yields the best
 * evaluation for the given player.
 */
int spMiniMaxNodeEvaluate(SPFiarGame* board, unsigned int depth, unsigned int maxDepth, bool sign);

#endif
