//
// Created by Dror on 2017-08-25.
//

#ifndef CHESS1_MOVES_H
#define CHESS1_MOVES_H

#include <stdlib.h>
#include <stdbool.h>

/**
 * Basic data structure to represent move from <y1, x1> to <y2, x2>.
 */
typedef struct move{
    unsigned char y1,x1,y2,x2;
} Move;

/**
 * A node for MoveList.
 */
typedef struct linked_move{
    Move* move;
    struct linked_move* next;
} LinkedMove;

/**
 * A linked list of moves, used to enumerate all possibilities for MiniMax algorithm.
 */
typedef struct move_list{
    LinkedMove* first;
} MoveList;

/**
 * Used by the minimax algorithm to return a move and an associated score.
 */
typedef struct scored_move{
    Move* move;
    int score;
} ScoredMove;

/**
 * Represents a past move for the purpose of undoing.
 */
typedef struct history_move{
    Move* move; // the original move
    char original; // the original value of the destination square
} HistoryMove;

//////

/**
 * Allocates a Move object.
 * @param y1 - origin y.
 * @param x1 - origin x.
 * @param y2 - dest y.
 * @param x2 - dest x.
 * @return
 */
Move* MoveCreate(unsigned char y1, unsigned char x1, unsigned char y2, unsigned char x2);

/**
 * Frees a Move object from memory.
 * @param move
 */
void MoveDestroy(Move* move);

/**
 * Allocates memory for a LinkedMove.
 * @param y1
 * @param x1
 * @param y2
 * @param x2
 * @return
 */
LinkedMove* LinkedMoveCreate(unsigned char y1, unsigned char x1, unsigned char y2, unsigned char x2);

/**
 * Frees a LinkedMove from memory, along with the associated data.
 * @param lmove
 */
void LinkedMoveDestroy(LinkedMove* lmove);

/**
 * Allocates a MoveList in memory.
 * @return
 */
MoveList* MoveListCreate();

/**
 * Frees a Movelist from memory.
 * @param list
 */
void MoveListDestroy(MoveList* list);

/**
 * Pushes a Move into the MoveList.
 * @param list - list into which to push.
 * @param y1
 * @param x1
 * @param y2
 * @param x2
 */
void MovePush(MoveList* list, unsigned char y1, unsigned char x1, unsigned char y2, unsigned char x2);

/**
 * Pops a LinkedMove from a MoveList.
 * @param list
 * @return
 */
LinkedMove* MovePop(MoveList* list);

/**
 * Checks whether a MoveList is empty. Used to see if there are any possible moves.
 * @param list
 * @return true if empty.
 */
bool isMoveListEmpty(MoveList* list);

/**
 * Allocates a ScoredMove in memory.
 * @param y1
 * @param x1
 * @param y2
 * @param x2
 * @param score - the score value for the move.
 * @return
 */
ScoredMove* ScoredMoveCreate(unsigned char y1, unsigned char x1, unsigned char y2, unsigned char x2, int score);

/**
 * Frees a ScoredMove from memory.
 * @param move
 */
void ScoredMoveDestroy(ScoredMove* move);

/**
 * Allocates a HistoryMove in memory.
 * @param y1
 * @param x1
 * @param y2
 * @param x2
 * @param original - the piece at <y2,x2> before the move was performed.
 * @return
 */
HistoryMove* HistoryMoveCreate(unsigned char y1, unsigned char x1, unsigned char y2, unsigned char x2, char original);

/**
 * Frees a HistoryMove from memory.
 * @param hist
 */
void HistoryMoveDestroy(HistoryMove* hist);

#endif //CHESS1_MOVES_H
