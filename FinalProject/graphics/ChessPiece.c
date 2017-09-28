//
// Created by Jonathan Gescheit on 9/27/17.
//

#include "ChessPiece.h"
//You need a create function:
ChessPiece* createChessPiece(SDL_Renderer* windowRender, SDL_Rect* location, PieceType type) {
    if (windowRender == NULL || location == NULL) {
        return NULL ;
    }
    //Allocate data
    ChessPiece* res = (ChessPiece*) malloc(sizeof(ChessPiece));
    const char* activeImage = "./assets/white_king.bmp";
    SDL_Surface* loadingSurface = SDL_LoadBMP(activeImage);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(windowRender, loadingSurface);
    if (res == NULL || loadingSurface == NULL || texture == NULL) {
        free(res);
        SDL_FreeSurface(loadingSurface); //It is safe to pass NULL
        SDL_DestroyTexture(texture); //It is safe to pass NULL
        return NULL ;
    }
    SDL_FreeSurface(loadingSurface); //Surface is not actually needed after texture is created
    res->texture = texture;
    res->location = spCopyRect(location);
    res->windowRenderer = windowRender;
    res->type = type;
    return res;
}

//You need this function in order to destroy all data Associate with a button:
void destroyChessPiece(ChessPiece* src) {
    if (src == NULL ) {
        return;
    }
    free(src->location);
    SDL_DestroyTexture(src->texture);
    free(src);
}

PIECE_CLICK_EVENT handleChessPieceEvent(ChessPiece *src, SDL_Event *event) {
    if (src == NULL || event == NULL ) {
        return PIECE_CLICKED_NONE; //Better to return an error value
    }

//    if (event->type == SDL_MOUSEBUTTONUP) {
//        SDL_Point point;
//        point.x = event->button.x;
//        point.y = event->button.y;
//        if (SDL_PointInRect(&point, src->location)) {
//            switch (src->type) {
//                case CHESS_BUTTON_NEW_GAME:
//                    return CHESS_CLICKED_NEW_GAME;
//                case CHESS_BUTTON_LOAD:
//                    return CHESS_CLICKED_LOAD;
//                case CHESS_BUTTON_QUIT:
//                    return CHESS_CLICKED_QUIT;
//                case CHESS_BUTTON_1PLAYER:
//                    return CHESS_CLICKED_1PLAYER;
//                case CHESS_BUTTON_2PLAYER:
//                    return CHESS_CLICKED_2PLAYER;
//                case CHESS_BUTTON_NOOB:
//                    return CHESS_CLICKED_NOOB;
//                case CHESS_BUTTON_EASY:
//                    return CHESS_CLICKED_EASY;
//                case CHESS_BUTTON_MODERATE:
//                    return CHESS_CLICKED_MODERATE;
//                case CHESS_BUTTON_HARD:
//                    return CHESS_CLICKED_HARD;
//                case CHESS_BUTTON_EXPERT:
//                    return CHESS_CLICKED_EXPERT;
//                case CHESS_BUTTON_WHITE:
//                    return CHESS_CLICKED_WHITE;
//                case CHESS_BUTTON_BLACK:
//                    return CHESS_CLICKED_BLACK;
//                case CHESS_BUTTON_BACK:
//                    return CHESS_CLICKED_BACK;
//                case CHESS_BUTTON_START:
//                    return CHESS_CLICKED_START;
//                default:
//                    return CHESS_CLICKED_NONE;
//            }
//        } else {
//            return CHESS_CLICKED_NONE;
//        }
//    } else {
//        return CHESS_CLICKED_NONE;
//    }
}

void drawChessPiece(ChessPiece* src) {
    if (src == NULL ) {
        return;
    }

    SDL_RenderCopy(src->windowRenderer, src->texture, NULL, src->location);
}

void toggleChessPiece(ChessPiece* src) {
    if (src == NULL) {
        return;
    }

    src->isActive = !src->isActive;
    drawChessPiece(src);
}