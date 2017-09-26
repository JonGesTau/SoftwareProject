//
// Created by Jonathan Gescheit on 9/22/17.
//

#include "ChessButton.h"

//You need a create function:
ChessButton* createChessButton(SDL_Renderer* windowRender, SDL_Rect* location, const char* activeImage, const char* inactiveImage, ButtonType type, bool isActive) {
    if (windowRender == NULL || location == NULL || activeImage == NULL || inactiveImage == NULL) {
        return NULL ;
    }
    //Allocate data
    ChessButton* res = (ChessButton*) malloc(sizeof(ChessButton));
    SDL_Surface* loadingSurfaceActive = SDL_LoadBMP(activeImage);
    SDL_Surface* loadingSurfaceInactive = SDL_LoadBMP(inactiveImage);
    SDL_Texture* activeTexture = SDL_CreateTextureFromSurface(windowRender, loadingSurfaceActive);
    SDL_Texture* inactiveTexture = SDL_CreateTextureFromSurface(windowRender, loadingSurfaceInactive);
    if (res == NULL || loadingSurfaceActive == NULL || loadingSurfaceInactive == NULL || activeTexture== NULL || inactiveTexture== NULL) {
        free(res);
        SDL_FreeSurface(loadingSurfaceActive); //It is safe to pass NULL
        SDL_FreeSurface(loadingSurfaceInactive); //It is safe to pass NULL
        SDL_DestroyTexture(activeTexture); //It is safe to pass NULL
        SDL_DestroyTexture(inactiveTexture); //It is safe to pass NULL
        return NULL ;
    }
    SDL_FreeSurface(loadingSurfaceActive); //Surface is not actually needed after texture is created
    SDL_FreeSurface(loadingSurfaceInactive); //Surface is not actually needed after texture is created
    res->activeTexture = activeTexture;
    res->inactiveTexture = inactiveTexture;
    res->location = spCopyRect(location);
    res->windowRenderer = windowRender;
    res->isActive = isActive;
    res->type = type;
    return res;
}

//You need this function in order to destroy all data Associate with a button:
void destroyChessButton(ChessButton* src) {
    if (src == NULL ) {
        return;
    }
    free(src->location);
    SDL_DestroyTexture(src->activeTexture);
    SDL_DestroyTexture(src->inactiveTexture);
    free(src);
}

BUTTON_CLICK_EVENT handleChessButtonEvent(ChessButton *src, SDL_Event *event) {
    if (src == NULL || event == NULL ) {
        return CHESS_CLICKED_NONE; //Better to return an error value
    }

    if (event->type == SDL_MOUSEBUTTONUP) {
        SDL_Point point;
        point.x = event->button.x;
        point.y = event->button.y;
        if (SDL_PointInRect(&point, src->location)) {
            switch (src->type) {
                case CHESS_BUTTON_NEW_GAME:
                    return CHESS_CLICKED_NEW_GAME;
                case CHESS_BUTTON_LOAD:
                    return CHESS_CLICKED_LOAD;
                case CHESS_BUTTON_QUIT:
                    return CHESS_CLICKED_QUIT;
                case CHESS_BUTTON_1PLAYER:
                    return CHESS_CLICKED_1PLAYER;
                case CHESS_BUTTON_2PLAYER:
                    return CHESS_CLICKED_2PLAYER;
                case CHESS_BUTTON_NOOB:
                    return CHESS_CLICKED_NOOB;
                case CHESS_BUTTON_EASY:
                    return CHESS_CLICKED_EASY;
                case CHESS_BUTTON_MODERATE:
                    return CHESS_CLICKED_MODERATE;
                case CHESS_BUTTON_HARD:
                    return CHESS_CLICKED_HARD;
                case CHESS_BUTTON_EXPERT:
                    return CHESS_CLICKED_EXPERT;
                case CHESS_BUTTON_WHITE:
                    return CHESS_CLICKED_WHITE;
                case CHESS_BUTTON_BLACK:
                    return CHESS_CLICKED_BLACK;
                case CHESS_BUTTON_BACK:
                    return CHESS_CLICKED_BACK;
                case CHESS_BUTTON_START:
                    return CHESS_CLICKED_START;
                default:
                    return CHESS_CLICKED_NONE;
            }
        } else {
            return CHESS_CLICKED_NONE;
        }
    } else {
        return CHESS_CLICKED_NONE;
    }
}

void drawChessButton(ChessButton* src) {
    if (src == NULL ) {
        return;
    }

    SDL_Texture* texture = src->isActive ? src->activeTexture : src->inactiveTexture;
    SDL_RenderCopy(src->windowRenderer, texture, NULL, src->location);
}

void toggleChessButton(ChessButton* src) {
    if (src == NULL) {
        return;
    }

    src->isActive = !src->isActive;
    drawChessButton(src);
}