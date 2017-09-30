//
// Created by jonathangescheit on 9/29/17.
//

#ifndef CHESS1_CHESSRECT_H
#define CHESS1_CHESSRECT_H
#include <SDL.h>
#include <SDL_video.h>
#include "ChessGUICommon.h"
#include <stdbool.h>


typedef enum {
    CHESS_RECT_COLOR_WHITE, CHESS_RECT_COLOR_GREY
} RectColor;

typedef enum {
    CHESS_DROP_RECT, RECT_CLICKED_NONE
} RECT_CLICK_EVENT;

typedef struct chess_rect {
    SDL_Texture* texture;
    SDL_Renderer* windowRenderer;
    SDL_Rect* location;
    RectColor color;
    int x;
    int y;
} ChessRect;

//You need a create function:
ChessRect *
createChessRect(SDL_Renderer *windowRender, SDL_Rect *location, RectColor color, int x, int y);

//You need this function in order to destroy all data Associate with a button:
void destroyChessRect(ChessRect*);

RECT_CLICK_EVENT handleChessRectEvent(ChessRect *src, SDL_Event *event);

void drawChessRect(ChessRect* src);
void toggleChessRect(ChessRect* src);

#endif //CHESS1_CHESSRECT_H
