//
// Created by Jonathan Gescheit on 9/22/17.
//

#include "ChessButton.h"
#include "ChessGUICommon.h"
#include "../MainAux.h"
#include "ChessMainWindow.h"

//You need a create function:
ChessButton* createChessButton(SDL_Renderer* windowRender, SDL_Rect* location, const char* image, ButtonType type) {
    if (windowRender == NULL || location == NULL || image == NULL ) {
        return NULL ;
    }
    //Allocate data
    ChessButton* res = (ChessButton*) malloc(sizeof(ChessButton));
    SDL_Surface* loadingSurface = SDL_LoadBMP(image); //We use the surface as a temp var;
    SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(windowRender,
                                                              loadingSurface);
    if (res == NULL || loadingSurface == NULL
        || buttonTexture == NULL) {
        free(res);
        SDL_FreeSurface(loadingSurface); //It is safe to pass NULL
        SDL_DestroyTexture(buttonTexture); ////It is safe to pass NULL
        return NULL ;
    }
    SDL_FreeSurface(loadingSurface); //Surface is not actually needed after texture is created
    res->buttonTexture = buttonTexture;
    res->location = spCopyRect(location);
    res->windowRenderer = windowRender;
    res->isActive = true;
    res->type = type;
    return res;
}

//You need this function in order to destroy all data Associate with a button:
void destroyChessButton(ChessButton* src) {
    if (src == NULL ) {
        return;
    }
    free(src->location);
    SDL_DestroyTexture(src->buttonTexture);
    free(src);
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
            if (src->type == CHESS_BUTTON_NEW_GAME) {
                return CHESS_CLICKED_NEW_GAME;
//                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Title", "New Game", NULL );
            } else if (src->type == CHESS_BUTTON_LOAD) {
                return CHESS_CLICKED_LOAD;
//                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Title", "Load", NULL );
            } else if (src->type == CHESS_BUTTON_QUIT) {
                return CHESS_CLICKED_QUIT;
//                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Title", "Quit", NULL );
            } else {
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
    SDL_RenderCopy(src->windowRenderer, src->buttonTexture, NULL,
                   src->location);
}