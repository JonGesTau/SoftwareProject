//
// Created by Dror on 2017-08-18.
//

#ifndef CHESS1_GAMEBOARD_H
#define CHESS1_GAMEBOARD_H

#include <stdbool.h>
#include <stdlib.h>

#define CH_PIECE_EMPTY 0
#define CH_PIECE_PAWN 1
#define CH_PIECE_BISHOP 2
#define CH_PIECE_KNIGHT 3
#define CH_PIECE_ROOK 4
#define CH_PIECE_QUEEN 5
#define CH_PIECE_KING 6
#define CH_PIECE_EMPTY 0



#define whichPiece(p) (abs(p))
#define isWhite(p) (p > 0)
#define isBlack(p) (p < 0)
#define chPieceScore(p) (((int[]){0,1,3,3,5,9,100})[whichPiece(p)])*(isBlack(p)?-1:1)
#define isLegalCoordinate(y, x) (y>-1 && y<8 && x>-1 && x<8)


typedef struct chess_gameboard{
    signed char board[8][8];
    bool whiteTurn;
    bool whiteOnBottom;
} GameBoard;

bool gameBoardIsLegalMove(GameBoard *game, char y1, char x1, char y2, char x2);

bool gameBoardIsLegalRookMove(GameBoard *game, char y1, char x1, char y2, char x2);
bool gameBoardIsLegalBishopMove(GameBoard *game, char y1, char x1, char y2, char x2);

void gameBoardSetup(GameBoard *game, bool whiteOnBottom);
GameBoard* gameBoardCopy(GameBoard* src);
void gameBoardDestroy(GameBoard* src);

bool gameBoardIsCheck(GameBoard *game, bool isWhite);
bool gameBoardIsMate(GameBoard *game, bool isWhite);

// all possible moves feature

#endif //CHESS1_GAMEBOARD_H
