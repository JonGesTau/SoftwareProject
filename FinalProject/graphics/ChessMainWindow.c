//
// Created by Jonathan Gescheit on 9/22/17.
//

#include "ChessMainWindow.h"

//Helper function to create buttons in the simple window;
ChessButton** createMainWindowChessButtons(SDL_Renderer *renderer) {
    if (renderer == NULL ) {
        return NULL ;
    }
    ChessButton** buttons = malloc(sizeof(ChessButton*));
    if (buttons == NULL ) {
        return NULL ;
    }

    SDL_Rect newGameR = { .x = 387, .y = 100, .h = 100, .w = 250 };
    SDL_Rect loadR = { .x = 387, .y = 250, .h = 100, .w = 250 };
    SDL_Rect quitR = { .x = 387, .y = 600, .h = 100, .w = 250 };

    buttons[0] = createChessButton(renderer, &newGameR, "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/NewGame.bmp", "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/NewGame.bmp", CHESS_BUTTON_NEW_GAME, true);
    buttons[1] = createChessButton(renderer, &loadR, "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/load.bmp", "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/load.bmp", CHESS_BUTTON_LOAD, true);
    buttons[2] = createChessButton(renderer, &quitR, "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/quit.bmp", "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/quit.bmp", CHESS_BUTTON_QUIT, true);

    if (buttons[0] == NULL || buttons[1] == NULL || buttons[2] == NULL) {
        destroyChessButton(buttons[0]); //NULL SAFE
        destroyChessButton(buttons[1]); //NULL SAFE
        destroyChessButton(buttons[2]); //NULL SAFE
        free(buttons);
        return NULL ;
    }
    return buttons;
}
ChessWindow* createMainWindow() {
    ChessWindow* res = malloc(sizeof(ChessWindow));
    ChessMainWindow* data = malloc(sizeof(ChessMainWindow));
    SDL_Window* window = SDL_CreateWindow("Tests", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    ChessButton** buttons = createMainWindowChessButtons(renderer);
    if (res == NULL || data == NULL || window == NULL || renderer == NULL
        || buttons == NULL ) {
        free(res);
        free(data);
        free(buttons);
        //We first destroy the renderer
        SDL_DestroyRenderer(renderer); //NULL safe
        SDL_DestroyWindow(window); //NULL safe
        return NULL ;
    }
    data->buttons = buttons;
    data->numOfButtons = 3;
    data->window = window;
    data->windowRenderer = renderer;
    res->data = (void*) data;
    res->destroyWindow = destroyMainWindow;
    res->drawWindow = drawMainWindow;
    res->handleEventWindow = handleEventMainWindow;
    return res;
}
void destroyMainWindow(ChessWindow* src) {
    if (src == NULL ) {
        return;
    }
    ChessMainWindow* data = (ChessMainWindow*) src->data;
    int i = 0;
    for (; i < 2; i++) {
        destroyChessButton(data->buttons[i]);//
    }
    free(data->buttons);
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
    for (; i < data->numOfButtons; i++) {
        drawChessButton(data->buttons[i]);
    }
    SDL_RenderPresent(data->windowRenderer);
}

CHESS_MAIN_EVENT handleEventMainWindow(ChessWindow* src, SDL_Event* event){
    if(src == NULL || event==NULL){
        return CHESS_MAIN_INVALID_ARGUMENT;
    }
    ChessMainWindow* data = (ChessMainWindow*)src->data;
    int i =0;
    for(;i<data->numOfButtons;i++){
        ChessButton* button = data->buttons[i];
        BUTTON_CLICK_EVENT clickEvent = handleChessButtonEvent(button, event);
        if (clickEvent == CHESS_CLICKED_NEW_GAME) {
            return CHESS_MAIN_START;
        } else if (clickEvent == CHESS_CLICKED_LOAD) {
            printf("LOAD ");
        } else if (clickEvent == CHESS_CLICKED_QUIT) {
            return CHESS_MAIN_EXIT;
        }
    }

    if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_CLOSE) return CHESS_MAIN_EXIT;

    return CHESS_MAIN_NONE;
}

void hideMainWindow(ChessMainWindow* src) {
    SDL_HideWindow(src->window);
}

void showMainWindow(ChessMainWindow* src) {
    SDL_ShowWindow(src->window);
}