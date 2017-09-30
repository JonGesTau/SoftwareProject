//
// Created by jonathangescheit on 9/29/17.
//

#include "ChessRect.h"
//You need a create function:
ChessRect *
createChessRect(SDL_Renderer *windowRender, SDL_Rect *location, RectColor color, ChessRect* piece, int x, int y) {
    if (windowRender == NULL || location == NULL) {
        return NULL ;
    }
    //Allocate data
    ChessRect* res = (ChessRect*) malloc(sizeof(ChessRect));
    if (res == NULL) {
        free(res);
        return NULL ;
    }
    res->location = spCopyRect(location);
    res->windowRenderer = windowRender;
    res->color = color;
    res->x = x;
    res->y = y;
    return res;
}

//You need this function in order to destroy all data Associate with a button:
void destroyChessRect(ChessRect* src) {
    if (src == NULL ) {
        return;
    }
    free(src->location);
    free(src);
}

RECT_CLICK_EVENT handleChessRectEvent(ChessRect *src, SDL_Event *event) {
    if (src == NULL || event == NULL ) {
        return RECT_CLICKED_NONE; //Better to return an error value
    }

    if (event->type == SDL_MOUSEBUTTONUP) {
        SDL_Point point;
        point.x = event->button.x;
        point.y = event->button.y;
        if (SDL_PointInRect(&point, src->location)) {
            return CHESS_DROP_RECT;
        } else {
            return RECT_CLICKED_NONE;
        }
    }
}

//void drawChessRect(ChessRect* src) {
//    if (src == NULL ) {
//        return;
//    }
//
//    if (src->color == CHESS_RECT_COLOR_GREY) {
//        SDL_SetRenderDrawColor(src->windowRenderer, 128, 128, 128, 0xFF);
//    } else {
//        SDL_SetRenderDrawColor(src->windowRenderer, 255, 255, 255, 0xFF);
//    }
//
//    SDL_RenderFillRect(src->windowRenderer, src->location);
//}