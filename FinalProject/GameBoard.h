//
// Created by Dror on 2017-08-18.
//

#ifndef CHESS1_GAMEBOARD_H
#define CHESS1_GAMEBOARD_H

#include <stdbool.h>
#include <stdlib.h>

#include "Moves.h"

#define CH_PIECE_EMPTY 0
#define CH_PIECE_PAWN 1
#define CH_PIECE_BISHOP 2
#define CH_PIECE_KNIGHT 3
#define CH_PIECE_ROOK 4
#define CH_PIECE_QUEEN 5
#define CH_PIECE_KING 6



#define whichPiece(p) (abs(p))
#define isWhite(p) (p > 0)
#define isBlack(p) (p < 0)
#define isEmpty(p) (p == CH_PIECE_EMPTY)
#define sign(p) (p>0 ? 1 : (p==0 ? 0 : -1))
#define chPieceScore(p) (((int[]){0,1,3,3,5,9,100})[whichPiece(p)])*(isBlack(p)?-1:1)
#define isLegalCoordinate(y, x) (y>-1 && y<8 && x>-1 && x<8)

// this data structure contains the board[y][x] and whose turn it is.
// used for game logic and should be wrapped inside a gameState object
typedef struct chess_gameboard{
    signed char board[8][8];
    bool whiteTurn;
} GameBoard;

// create, copy and destroy
GameBoard* gameBoardCreate();
GameBoard* gameBoardCopy(GameBoard* src);
void gameBoardDestroy(GameBoard* src);

// clears the board and places the pieces for a new game
void gameBoardSetup(GameBoard *game);


// given a board, determines if the move (y1,x1)->(y2,x2) is legal
bool gameBoardIsLegalMove(GameBoard *game, char y1, char x1, char y2, char x2);

// two sub procedures of the above function
bool gameBoardIsLegalRookMove(GameBoard *game, char y1, char x1, char y2, char x2);
bool gameBoardIsLegalBishopMove(GameBoard *game, char y1, char x1, char y2, char x2);

// moves piece from (y1,x1) to (y2,x2), assumes move is legal
bool gameBoardPerformMove(GameBoard* game, char y1, char x1, char y2, char x2);

// don't call this directly, use GameStateUndo instead
bool gameBoardUndoMove(GameBoard* game, HistoryMove* hist);

// returns true if piece at (y1,x1) is threatened
bool gameBoardIsThreatened(GameBoard *game, char y1, char x1);

// finds white/black king and returns true if threatened, uses the above function
bool gameBoardIsCheck(GameBoard *game, bool isWhite);

bool gameBoardIsMate(GameBoard *game, bool isWhite);

// checks whether there is a tie given isWhite's turn to play
bool gameBoardIsStalemate(GameBoard *game, bool isWhite);


// all possible moves feature
MoveList* gameBoardAllMoves(GameBoard* game, bool isWhite);

void gameBoardMovesPawn(GameBoard* game, MoveList* moves, char y, char x);
void gameBoardMovesBishop(GameBoard* game, MoveList* moves, char y, char x);
void gameBoardMovesKnight(GameBoard* game, MoveList* moves, char y, char x);
void gameBoardMovesRook(GameBoard* game, MoveList* moves, char y, char x);
void gameBoardMovesKing(GameBoard* game, MoveList* moves, char y, char x);

#endif //CHESS1_GAMEBOARD_H
