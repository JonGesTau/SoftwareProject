//
// Created by Dror on 2017-08-25.
//

/*
 * This file offers two data structures dealing with moves:
 * 1. LinkedMoves - so we can dynamically store lists of possible moves,
 *     this is good for min/max and also for the possible moves feature
 * 2. ScoredMove - also for min/max, we return the best move along with the assocated score
 *
 * Todo: quite possibly we only need y2,x2 for LinkedMove, since it is easy to remember y1,x1
 */

#ifndef CHESS1_MOVES_H
#define CHESS1_MOVES_H

#include <stdlib.h>

typedef struct move{
    char y1,x1,y2,x2;
} Move;

typedef struct linked_move{
    Move* move;
    struct linked_move* next;
} LinkedMove;

typedef struct move_list{
    LinkedMove* first;
} MoveList;

typedef struct scored_move{
    Move* move;
    int score;
} ScoredMove;

//
Move* MoveCreate(char y1, char x1, char y2, char x2);
void MoveDestroy(Move* move);

// a node in the move linked list
LinkedMove* LinkedMoveCreate(char y1, char x1, char y2, char x2);
void LinkedMoveDestroy(LinkedMove* lmove);

//// MoveList is a linked list of moves for variable-size lists of moves
// used in minimax and all possible moves to keep all possibilites in memory
MoveList* MoveListCreate();

void MovePush(MoveList* list, char y1, char x1, char y2, char x2);

Move* MovePop(MoveList* list);

void MoveListDestroy(MoveList* list);

/// for minimax algorihm, we use this data sructure to return a certain move with a score
ScoredMove* ScoredMoveCreate(char y1, char x1, char y2, char x2, int score);
void ScoredMoveDestroy(ScoredMove* move);



#endif //CHESS1_MOVES_H
