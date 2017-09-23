//
// Created by Jonathan Gescheit on 9/22/17.
//

#include "ChessSettingsWindow.h"

//Helper function to create buttons in the simple window;
ChessButton** createSettingsWindowChessButtons(SDL_Renderer *renderer, GameSettings *settings) {
    if (renderer == NULL ) {
        return NULL ;
    }
    ChessButton** buttons = malloc(sizeof(ChessButton*));
    if (buttons == NULL ) {
        return NULL ;
    }

    SDL_Rect onePlayer = { .x = 200, .y = 50, .h = 100, .w = 250 };
    SDL_Rect twoPlayer = { .x = 600, .y = 50, .h = 100, .w = 250 };

    SDL_Rect noob = { .x = 50, .y = 200, .h = 100, .w = 250 };
    SDL_Rect easy = { .x = 350, .y = 200, .h = 100, .w = 250 };
    SDL_Rect moderate = { .x = 650, .y = 200, .h = 100, .w = 250 };
    SDL_Rect hard = { .x = 150, .y = 350, .h = 100, .w = 250 };
    SDL_Rect expert = { .x = 450, .y = 350, .h = 100, .w = 250 };

    SDL_Rect white = { .x = 200, .y = 500, .h = 100, .w = 250 };
    SDL_Rect black = { .x = 600, .y = 500, .h = 100, .w = 250 };

    buttons[0] = createChessButton(renderer, &onePlayer, "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/oneplayer_active.bmp", "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/oneplayer_inactive.bmp", CHESS_BUTTON_1PLAYER, false);
    buttons[1] = createChessButton(renderer, &twoPlayer, "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/twoplayer_active.bmp", "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/twoplayer_inactive.bmp", CHESS_BUTTON_2PLAYER, false);
    buttons[2] = createChessButton(renderer, &noob, "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/noob_active.bmp", "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/noob_inactive.bmp", CHESS_BUTTON_NOOB, false);
    buttons[3] = createChessButton(renderer, &easy, "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/easy_active.bmp", "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/easy_inactive.bmp", CHESS_BUTTON_EASY, false);
    buttons[4] = createChessButton(renderer, &moderate, "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/moderate_active.bmp", "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/moderate_inactive.bmp", CHESS_BUTTON_MODERATE, false);
    buttons[5] = createChessButton(renderer, &hard, "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/hard_active.bmp", "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/hard_inactive.bmp", CHESS_BUTTON_HARD, false);
    buttons[6] = createChessButton(renderer, &expert, "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/expert_active.bmp", "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/expert_inactive.bmp", CHESS_BUTTON_EXPERT, false);
    buttons[7] = createChessButton(renderer, &white, "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/white_active.bmp", "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/white_inactive.bmp", CHESS_BUTTON_WHITE, false);
    buttons[8] = createChessButton(renderer, &black, "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/black_active.bmp", "/Users/jonathangescheit/TAU/SoftwareProject/FinalProject/black_inactive.bmp", CHESS_BUTTON_BLACK, false);

    if (buttons[0] == NULL || buttons[1] == NULL) {
        destroyChessButton(buttons[0]); //NULL SAFE
        destroyChessButton(buttons[1]); //NULL SAFE
        free(buttons);
        return NULL ;
    }

    if (settings->gameMode == 1) {
        buttons[0]->isActive = true;
    } else {
        buttons[1]->isActive = true;
    }

    if (settings->difficulty == 1) {
        buttons[2]->isActive = true;
    } else if (settings->difficulty == 2) {
        buttons[3]->isActive = true;
    } else if (settings->difficulty == 3) {
        buttons[4]->isActive = true;
    } else if (settings->difficulty == 4) {
        buttons[5]->isActive = true;
    } else if (settings->difficulty == 5) {
        buttons[6]->isActive = true;
    }

    if (settings->userColor) {
        buttons[7]->isActive = true;
    } else {
        buttons[8]->isActive = true;
    }

    return buttons;
}
ChessSettingsWindow* createSettingsWindow() {
    ChessSettingsWindow* res = malloc(sizeof(ChessSettingsWindow));
//    ChessSettingsWindow* data = malloc(sizeof(ChessSettingsWindow));
    SDL_Window* window = SDL_CreateWindow("Tests", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    ChessButton** buttons = createSettingsWindowChessButtons(renderer, getDefaultSettings());
    if (res == NULL || window == NULL || renderer == NULL || buttons == NULL ) {
        free(res);
        free(buttons);
        //We first destroy the renderer
        SDL_DestroyRenderer(renderer); //NULL safe
        SDL_DestroyWindow(window); //NULL safe
        return NULL ;
    }
    res->buttons = buttons;
    res->numOfButtons = 9;
    res->window = window;
    res->windowRenderer = renderer;
    res->settings = getDefaultSettings();

    return res;
}
void destroySettingsWindow(ChessSettingsWindow *src) {
    if (src == NULL ) {
        return;
    }

    int i = 0;
    for (; i < 2; i++) {
        destroyChessButton(src->buttons[i]);//
    }
    free(src->buttons);
    free(src->settings);
    SDL_DestroyRenderer(src->windowRenderer);
    SDL_DestroyWindow(src->window);

    free(src);
}
void drawSettingsWindow(ChessSettingsWindow *src) {
    if (src == NULL ) {
        return;
    }

    //Draw window
    SDL_SetRenderDrawColor(src->windowRenderer, 255, 255, 255, 255);
    SDL_RenderClear(src->windowRenderer);
    int i = 0;
    for (; i < src->numOfButtons; i++) {
        drawChessButton(src->buttons[i]);
    }
    SDL_RenderPresent(src->windowRenderer);
}

CHESS_SETTINGS_EVENT handleEventSettingsWindow(ChessSettingsWindow *src, SDL_Event *event){
    if(src == NULL || event==NULL){
        return CHESS_SETTINGS_EXIT;
    }

    int i =0;
    for(;i<src->numOfButtons;i++){
        ChessButton* button = src->buttons[i];
        BUTTON_CLICK_EVENT clickEvent = handleChessButtonEvent(button, event);
        // TODO: Refactor handling functions
        switch (clickEvent) {
            case CHESS_CLICKED_1PLAYER:
                if (src->settings->gameMode != 1) {
                    src->settings->gameMode = 1;
                    printf("Mode is %d\n", src->settings->gameMode);
                    toggleChessButton(src->buttons[0]);
                    toggleChessButton(src->buttons[1]);
                }
                break;
            case CHESS_CLICKED_2PLAYER:
                if (src->settings->gameMode != 2) {
                    src->settings->gameMode = 2;
                    printf("Mode is %d\n", src->settings->gameMode);
                    toggleChessButton(src->buttons[0]);
                    toggleChessButton(src->buttons[1]);
                }
                break;
            case CHESS_CLICKED_NOOB:
                if (src->settings->difficulty != 1) {
                    src->settings->difficulty = 1;
                    printf("Difficulty is %d\n", src->settings->difficulty);
                    int j = 2;
                    for (;j<7; j++) {
                        if (src->buttons[j]->isActive) toggleChessButton(src->buttons[j]);
                    }
                    toggleChessButton(button);
                }
                break;
            case CHESS_CLICKED_EASY:
                if (src->settings->difficulty != 2) {
                    src->settings->difficulty = 2;
                    printf("Difficulty is %d\n", src->settings->difficulty);
                    int j = 2;
                    for (;j<7; j++) {
                        if (src->buttons[j]->isActive) toggleChessButton(src->buttons[j]);
                    }
                    toggleChessButton(button);
                }
                break;
            case CHESS_CLICKED_MODERATE:
                if (src->settings->difficulty != 3) {
                    src->settings->difficulty = 3;
                    printf("Difficulty is %d\n", src->settings->difficulty);
                    int j = 2;
                    for (;j<7; j++) {
                        if (src->buttons[j]->isActive) toggleChessButton(src->buttons[j]);
                    }
                    toggleChessButton(button);
                }
                break;
            case CHESS_CLICKED_HARD:
                if (src->settings->difficulty != 4) {
                    src->settings->difficulty = 4;
                    printf("Difficulty is %d\n", src->settings->difficulty);
                    int j = 2;
                    for (;j<7; j++) {
                        if (src->buttons[j]->isActive) toggleChessButton(src->buttons[j]);
                    }
                    toggleChessButton(button);
                }
                break;
            case CHESS_CLICKED_EXPERT:
                if (src->settings->difficulty != 5) {
                    src->settings->difficulty = 5;
                    printf("Difficulty is %d\n", src->settings->difficulty);
                    int j = 2;
                    for (;j<7; j++) {
                        if (src->buttons[j]->isActive) toggleChessButton(src->buttons[j]);
                    }
                    toggleChessButton(button);
                }
                break;
            case CHESS_CLICKED_WHITE:
                if (!src->settings->userColor) {
                    src->settings->userColor = 1;
                    printf("Color is %d\n", src->settings->userColor);
                    toggleChessButton(src->buttons[7]);
                    toggleChessButton(src->buttons[8]);
                }
                break;
            case CHESS_CLICKED_BLACK:
                if (src->settings->userColor) {
                    src->settings->userColor = 0;
                    printf("Color is %d\n", src->settings->userColor);
                    toggleChessButton(src->buttons[7]);
                    toggleChessButton(src->buttons[8]);
                }
                break;
        }
    }

    if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_CLOSE) return CHESS_SETTINGS_EXIT;

    return CHESS_CLICKED_NONE;
}

void hideSettingsWindow(ChessSettingsWindow* src) {
    SDL_HideWindow(src->window);
}

void showSettingsWindow(ChessSettingsWindow* src) {
    SDL_ShowWindow(src->window);
}