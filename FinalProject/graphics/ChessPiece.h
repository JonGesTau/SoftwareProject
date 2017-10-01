//
// Created by Jonathan Gescheit on 9/27/17.
//

// Represents a gameplay piece

#ifndef CHESS1_CHESSPIECE_H
#define CHESS1_CHESSPIECE_H
#include <stdbool.h>
#include <SDL.h>
#include <SDL_video.h>
#include "ChessGUICommon.h"
#include "../GameBoard.h"

#define blackPawnImg "./assets/black_pawn.bmp"
#define blackBishopImg "./assets/black_bishop.bmp"
#define blackKnightImg "./assets/black_Knight.bmp"
#define blackRookImg "./assets/black_rook.bmp"
#define blackQueenImg "./assets/black_queen.bmp"
#define blackKingImg "./assets/black_king.bmp"
#define whitePawnImg "./assets/white_pawn.bmp"
#define whiteBishopImg "./assets/white_bishop.bmp"
#define whiteKnightImg "./assets/white_knight.bmp"
#define whiteRookImg "./assets/white_rook.bmp"
#define whiteQueenImg "./assets/white_queen.bmp"
#define whiteKingImg "./assets/white_king.bmp"


/**
 * Used to determine piece type
 */
typedef enum {
    CHESS_PIECE_EMPTY, CHESS_PIECE_PAWN, CHESS_PIECE_BISHOP, CHESS_PIECE_KNIGHT, CHESS_PIECE_ROOK, CHESS_PIECE_QUEEN, CHESS_PIECE_KING
} PieceType;

/**
 * Used to determine piece color
 */
typedef enum {
    CHESS_PIECE_COLOR_WHITE, CHESS_PIECE_COLOR_BLACK
} PieceColor;

/**
 * Used to determine what the user does with the piece
 */
typedef enum {
    CHESS_DRAG_PIECE, CHESS_DROP_PIECE, PIECE_CLICKED_NONE, CHESS_MOTION_PIECE
} PIECE_CLICK_EVENT;

/**
 * Represents the piece itself
 */
typedef struct chess_piece {
    SDL_Texture* texture;
    SDL_Renderer* windowRenderer;
    SDL_Rect* location;
    bool isActive;
    PieceType type;
    PieceColor color;
    bool isDragged;
    int x;
    int y;
    SDL_Rect *previousLocation;
} ChessPiece;

/**
 * Create a game piece
 * @param windowRender
 * @param location
 * @param type
 * @param color
 * @param x
 * @param y
 * @return piece
 */
ChessPiece* createChessPiece(SDL_Renderer *windowRender, SDL_Rect *location, PieceType type, PieceColor color, int x, int y);

/**
 * Destroy game piece
 */
void destroyChessPiece(ChessPiece*);

/**
 * Handle a game piece event (drag, drop, etc)
 * @param src
 * @param event
 * @return event
 */
PIECE_CLICK_EVENT handleChessPieceEvent(ChessPiece *src, SDL_Event *event);

/**
 * Draw piece on screen
 * @param src
 */
void drawChessPiece(ChessPiece* src);

/**
 * Get the correct piece image to draw
 * @param type
 * @param color
 * @return piece image path
 */
char* getPieceImg(PieceType type, PieceColor color);

#endif //CHESS1_CHESSPIECE_H
