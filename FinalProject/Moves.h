//
// Created by Dror on 2017-08-25.
//

/*
 * This file offers two data structures dealing with moves:
 * 1. LinkedMoves - so we can dynamically store lists of possible moves,
 *     this is good for min/max and also for the possible moves feature
 * 2. ScoredMove - also for min/max, we return the best move along with the assocated score
 *
 * Todo: quite possbly we only need y2,x2 for LinkedMove, since it is easy to remember y1,x1
 */

#ifndef CHESS1_MOVES_H
#define CHESS1_MOVES_H

#include <stdlib.h>

typedef struct linked_move{
    char y1,x1,y2,x2;
    struct linked_move* next;
} LinkedMove;

typedef struct move_list{
    LinkedMove* first;
} MoveList;

typedef struct scored_move{
    char y1,x1,y2,x2;
    int score;
} ScoredMove;

typedef struct move{
    int y1,x1,y2,x2;
} Move;

////

MoveList* MoveListCreate();

void MovePush(MoveList* list, char y1, char x1, char y2, char x2);

LinkedMove* MovePop(MoveList* list);

void MoveListDestroy(MoveList* list);

///

ScoredMove* ScoredMoveCreate(char y1, char x1, char y2, char x2, int score);
void ScoredMoveDestroy(ScoredMove* move);



#endif //CHESS1_MOVES_H
