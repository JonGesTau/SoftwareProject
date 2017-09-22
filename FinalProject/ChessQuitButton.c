//
// Created by Jonathan Gescheit on 9/22/17.
//

#include "ChessQuitButton.h"
#include "ChessGUICommon.h"

//You need a create function:
ChessWidget* createChessQuitButton(SDL_Renderer* windowRender, SDL_Rect* location,
                                   const char* image) {
    if (windowRender == NULL || location == NULL || image == NULL ) {
        return NULL ;
    }
    //Allocate data
    ChessWidget* res = (ChessWidget*) malloc(sizeof(ChessWidget));
    ChessQuitButton* data = (ChessQuitButton*) malloc(sizeof(ChessQuitButton));
    SDL_Surface* loadingSurface = SDL_LoadBMP(image); //We use the surface as a temp var;
    SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(windowRender,
                                                              loadingSurface);
    if (res == NULL || data == NULL || loadingSurface == NULL
        || buttonTexture == NULL) {
        free(res);
        free(data);
        SDL_FreeSurface(loadingSurface); //It is safe to pass NULL
        SDL_DestroyTexture(buttonTexture); ////It is safe to pass NULL
        return NULL ;
    }
    SDL_FreeSurface(loadingSurface); //Surface is not actually needed after texture is created
    data->buttonTexture = buttonTexture;
    data->location = spCopyRect(location);
    data->windowRenderer = windowRender;
    res->destroyWidget = destroyChessQuitButton;
    res->drawWidget = drawChessQuitButton;
    res->handleEvent = handleChessQuitButtonEvenet;
    res->data = data;
    return res;
}

//You need this function in order to destroy all data Associate with a button:
void destroyChessQuitButton(ChessWidget* src) {
    if (src == NULL ) {
        return;
    }
    ChessQuitButton* castData = (ChessQuitButton*) src->data;
    free(castData->location);
    SDL_DestroyTexture(castData->buttonTexture);
    free(castData);
    free(src);
}

void handleChessQuitButtonEvenet(ChessWidget* src, SDL_Event* event) {
    if (src == NULL || event == NULL ) {
        return; //Better to return an error value
    }
    ChessQuitButton* castData = (ChessQuitButton*) src->data;
    if (event->type == SDL_MOUSEBUTTONUP) {
        SDL_Point point;
        point.x = event->button.x;
        point.y = event->button.y;
        if (SDL_PointInRect(&point, castData->location)) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Title",
                                     "We did it", NULL );
        }
    } else {
        return;
    }
}

void drawChessQuitButton(ChessWidget* src) {
    if (src == NULL ) {
        return;
    }
    ChessQuitButton* castData = (ChessQuitButton*) src->data;
    SDL_RenderCopy(castData->windowRenderer, castData->buttonTexture, NULL,
                   castData->location);
}