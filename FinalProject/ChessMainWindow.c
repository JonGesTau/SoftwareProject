//
// Created by Jonathan Gescheit on 9/22/17.
//

#include "ChessMainWindow.h"
#include "ChessNewGameButton.h"
#include "ChessLoadButton.h"
#include "ChessQuitButton.h"

//Helper function to create buttons in the simple window;
ChessWidget** createMainWindowChessWidgets(SDL_Renderer* renderer) {
    if (renderer == NULL ) {
        return NULL ;
    }
    ChessWidget** widgets = malloc(sizeof(ChessWidget*));
    if (widgets == NULL ) {
        return NULL ;
    }

    SDL_Rect newGameR = { .x = 387, .y = 100, .h = 100, .w = 250 };
    SDL_Rect loadR = { .x = 387, .y = 250, .h = 100, .w = 250 };
    SDL_Rect quitR = { .x = 387, .y = 600, .h = 100, .w = 250 };

    widgets[0] = createChessNewGameButton(renderer, &newGameR, "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/NewGame.bmp");
    widgets[1] = createChessLoadButton(renderer, &loadR, "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/load.bmp");
    widgets[2] = createChessQuitButton(renderer, &quitR, "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/quit.bmp");

    if (widgets[0] == NULL || widgets[1] == NULL || widgets[2] == NULL) {
        destroyWidget(widgets[0]); //NULL SAFE
        destroyWidget(widgets[1]); //NULL SAFE
        destroyWidget(widgets[2]); //NULL SAFE
        free(widgets);
        return NULL ;
    }
    return widgets;
}
ChessWindow* createMainWindow() {
    ChessWindow* res = malloc(sizeof(ChessWindow));
    ChessMainWindow* data = malloc(sizeof(ChessMainWindow));
    SDL_Window* window = SDL_CreateWindow("Tests", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
                                                SDL_RENDERER_ACCELERATED);
    ChessWidget** widgets = createMainWindowChessWidgets(renderer);
    if (res == NULL || data == NULL || window == NULL || renderer == NULL
        || widgets == NULL ) {
        free(res);
        free(data);
        free(widgets);
        //We first destroy the renderer
        SDL_DestroyRenderer(renderer); //NULL safe
        SDL_DestroyWindow(window); //NULL safe
        return NULL ;
    }
    data->widgets = widgets;
    data->numOfWidgets = 3;
    data->window = window;
    data->windowRenderer = renderer;
    data->widgets = widgets;
    res->data = (void*) data;
    res->destroyWindow = destroyMainWindow;
    res->drawWindow = drawMainWindow;
    res->handleEventWindow = handleEvenetMainWindow;
    return res;
}
void destroyMainWindow(ChessWindow* src) {
    if (src == NULL ) {
        return;
    }
    ChessMainWindow* data = (ChessMainWindow*) src->data;
    int i = 0;
    for (; i < 2; i++) {
        destroyWidget(data->widgets[i]);//
    }
    free(data->widgets);
    SDL_DestroyRenderer(data->windowRenderer);
    SDL_DestroyWindow(data->window);
    free(data);
    free(src);
}
void drawMainWindow(ChessWindow* src) {
    if (src == NULL ) {
        return;
    }
    ChessMainWindow* data = (ChessMainWindow*) src->data;
    //Draw window
    SDL_SetRenderDrawColor(data->windowRenderer, 255, 255, 255, 255);
    SDL_RenderClear(data->windowRenderer);
    int i = 0;
    for (; i < data->numOfWidgets; i++) {
        (data->widgets[i])->drawWidget(data->widgets[i]);
    }
    SDL_RenderPresent(data->windowRenderer);
}

void handleEvenetMainWindow(ChessWindow* src, SDL_Event* event){
    if(src == NULL || event==NULL){
        return;
    }
    ChessMainWindow* data = (ChessMainWindow*)src->data;
    int i =0;
    for(;i<data->numOfWidgets;i++){
        data->widgets[i]->handleEvent(data->widgets[i],event);
    }
    return;
}