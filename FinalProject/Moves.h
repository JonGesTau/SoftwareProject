//
// Created by Dror on 2017-08-25.
//

/*
 * This file offers two data structures dealing with moves:
 * 1. LinkedMoves - so we can dynamically store lists of possible moves,
 *     this is good for min/max and also for the possible moves feature
 * 2. ScoredMove - also for min/max, we return the best move along with the assocated score
 *
 *
 */

#ifndef CHESS1_MOVES_H
#define CHESS1_MOVES_H

#include <stdlib.h>
#include <stdbool.h>

// Basic data structure to represent move from <y1, x1> to <y2, x2>
typedef struct move{
    unsigned char y1,x1,y2,x2;
} Move;

// a node containing a move for MoveList
typedef struct linked_move{
    Move* move;
    struct linked_move* next;
} LinkedMove;

// a linked list of moves
typedef struct move_list{
    LinkedMove* first;
} MoveList;

// representation of data
typedef struct scored_move{
    Move* move;
    int score;
} ScoredMove;

// saves past move for undoing
typedef struct history_move{
    Move* move; // the original move
    char original; // the original value of the destination square
} HistoryMove;

//////
Move* MoveCreate(unsigned char y1, unsigned char x1, unsigned char y2, unsigned char x2);
void MoveDestroy(Move* move);

// a node in the move linked list
LinkedMove* LinkedMoveCreate(unsigned char y1, unsigned char x1, unsigned char y2, unsigned char x2);
void LinkedMoveDestroy(LinkedMove* lmove);

//// MoveList is a linked list of moves for variable-size lists of moves
// used in minimax and all possible moves to keep all possibilites in memory
MoveList* MoveListCreate();

void MovePush(MoveList* list, unsigned char y1, unsigned char x1, unsigned char y2, unsigned char x2);

LinkedMove* MovePop(MoveList* list);

void MoveListDestroy(MoveList* list);

bool isMoveListEmpty(MoveList* list);

/// for minimax algorihm, we use this data sructure to return a certain move with a score
ScoredMove* ScoredMoveCreate(unsigned char y1, unsigned char x1, unsigned char y2, unsigned char x2, int score);
void ScoredMoveDestroy(ScoredMove* move);

////
HistoryMove* HistoryMoveCreate(unsigned char y1, unsigned char x1, unsigned char y2, unsigned char x2, char original);
void HistoryMoveDestroy(HistoryMove* hist);


#endif //CHESS1_MOVES_H
