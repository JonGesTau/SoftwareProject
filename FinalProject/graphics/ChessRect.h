//
// Created by jonathangescheit on 9/29/17.
//

// Represents the rectangles of the chess board. Used to know where a piece is dropped and it's location.

#ifndef CHESS1_CHESSRECT_H
#define CHESS1_CHESSRECT_H
#include <SDL.h>
#include <SDL_video.h>
#include "ChessGUICommon.h"
#include <stdbool.h>


/**
 * Used to determine the rectangle's color
 */
typedef enum {
    CHESS_RECT_COLOR_WHITE, CHESS_RECT_COLOR_GREY
} RectColor;

/**
 * Used to determine if a piece was dropped on the rectangle
 */
typedef enum {
    CHESS_DROP_RECT, RECT_CLICKED_NONE
} RECT_CLICK_EVENT;

/**
 * The rectangle itself
 */
typedef struct chess_rect {
    SDL_Texture* texture;
    SDL_Renderer* windowRenderer;
    SDL_Rect* location;
    RectColor color;
    int x;
    int y;
} ChessRect;

/**
 * Create chess rectangle
 * @param windowRender
 * @param location
 * @param color
 * @param x
 * @param y
 * @return rectangle
 */
ChessRect* createChessRect(SDL_Renderer *windowRender, SDL_Rect *location, RectColor color, int x, int y);

/**
 * Destroy chess rectangle
 */
void destroyChessRect(ChessRect*);

/**
 * Handle event of rectangle (a piece dropped on it for example)
 * @param src
 * @param event
 * @return event
 */
RECT_CLICK_EVENT handleChessRectEvent(ChessRect *src, SDL_Event *event);

#endif //CHESS1_CHESSRECT_H
