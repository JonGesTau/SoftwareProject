//
// Created by Jonathan Gescheit on 9/22/17.
//

#include "ChessSettingsWindow.h"

//Helper function to create buttons in the simple window;
ChessButton ** createSettingsWindowChessButtons(SDL_Renderer *renderer) {
    if (renderer == NULL ) {
        return NULL ;
    }
    ChessButton** buttons = malloc(sizeof(ChessButton*));
    if (buttons == NULL ) {
        return NULL ;
    }

    SDL_Rect newGameR = { .x = 387, .y = 100, .h = 100, .w = 250 };

    buttons[0] = createChessButton(renderer, &newGameR, "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/NewGame.bmp", CHESS_BUTTON_NEW_GAME);

    if (buttons[0] == NULL || buttons[1] == NULL || buttons[2] == NULL) {
        destroyChessButton(buttons[0]); //NULL SAFE
        free(buttons);
        return NULL ;
    }
    return buttons;
}
ChessWindow* createSettingsWindow() {
    ChessWindow* res = malloc(sizeof(ChessWindow));
    ChessSettingsWindow* data = malloc(sizeof(ChessSettingsWindow));
    SDL_Window* window = SDL_CreateWindow("Tests", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    ChessButton** buttons = createSettingsWindowChessButtons(renderer);
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
    data->numOfButtons = 1;
    data->window = window;
    data->windowRenderer = renderer;
    res->data = (void*) data;
    res->destroyWindow = destroySettingsWindow;
    res->drawWindow = drawSettingsWindow;
    res->handleEventWindow = handleEventSettingsWindow;
    return res;
}
void destroySettingsWindow(ChessWindow* src) {
    if (src == NULL ) {
        return;
    }
    ChessSettingsWindow* data = (ChessSettingsWindow*) src->data;
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
void drawSettingsWindow(ChessWindow* src) {
    if (src == NULL ) {
        return;
    }
    ChessSettingsWindow* data = (ChessSettingsWindow*) src->data;
    //Draw window
    SDL_SetRenderDrawColor(data->windowRenderer, 255, 255, 255, 255);
    SDL_RenderClear(data->windowRenderer);
    int i = 0;
    for (; i < data->numOfButtons; i++) {
        drawChessButton(data->buttons[i]);
    }
    SDL_RenderPresent(data->windowRenderer);
}

CHESS_SETTINGS_EVENT handleEventSettingsWindow(ChessWindow* src, SDL_Event* event){
    if(src == NULL || event==NULL){
        return CHESS_CLICKED_NONE;
    }
    ChessSettingsWindow* data = (ChessSettingsWindow*)src->data;
    int i =0;
    for(;i<data->numOfButtons;i++){
        ChessButton* button = data->buttons[i];
        BUTTON_CLICK_EVENT clickEvent = handleChessButtonEvent(button, event);
        if (clickEvent == CHESS_CLICKED_NEW_GAME) {
            printf("NEW GAME ");
        } else if (clickEvent == CHESS_CLICKED_LOAD) {
            printf("LOAD ");
        } else if (clickEvent == CHESS_CLICKED_QUIT) {
            printf("QUIT ");
        }
    }

    return CHESS_CLICKED_NONE;
}

void hideSettingsWindow(ChessSettingsWindow* src) {
    SDL_HideWindow(src->window);
}

void showSettingsWindow(ChessSettingsWindow* src) {
    SDL_ShowWindow(src->window);
}