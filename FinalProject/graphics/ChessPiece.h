//
// Created by Jonathan Gescheit on 9/27/17.
//

#ifndef CHESS1_CHESSPIECE_H
#define CHESS1_CHESSPIECE_H
#include <stdbool.h>
#include <SDL.h>
#include <SDL_video.h>
#include "ChessGUICommon.h"
#include "../GameBoard.h"

typedef enum {
    CHESS_PIECE_EMPTY, CHESS_PIECE_PAWN, CHESS_PIECE_BISHOP, CHESS_PIECE_KNIGHT, CHESS_PIECE_ROOK, CHESS_PIECE_QUEEN, CHESS_PIECE_KING
} PieceType;

typedef enum {
    CHESS_DRAG_PIECE, CHESS_DROP_PIECE, PIECE_CLICKED_NONE
} PIECE_CLICK_EVENT;

typedef struct chess_piece {
    SDL_Texture* texture;
    SDL_Renderer* windowRenderer;
    SDL_Rect* location;
    bool isActive;
    PieceType type;
} ChessPiece;

//You need a create function:
ChessPiece* createChessPiece(SDL_Renderer* windowRender, SDL_Rect* location, PieceType type);

//You need this function in order to destroy all data Associate with a button:
void destroyChessPiece(ChessPiece*);

PIECE_CLICK_EVENT handleChessPieceEvent(ChessPiece *src, SDL_Event *event);

void drawChessPiece(ChessPiece* src);
void toggleChessPiece(ChessPiece* src);


#endif //CHESS1_CHESSPIECE_H
