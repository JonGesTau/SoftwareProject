#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_

#define SP_MINI_MAX_NODE_PLAYER_VAL(p) (p == SP_FIAR_GAME_EMPTY_ENTRY ? 0 : (p == SP_FIAR_GAME_PLAYER_1_SYMBOL ? 1 : -1))

#include "SPFIARGame.h"

//Put all decleartions and constants here
int spMiniMaxNodeScore(SPFiarGame* board);
int spMiniMaxNodeEvaluate(SPFiarGame* board, unsigned int depth, unsigned int maxDepth, bool sign);

#endif
