//
// Created by jonathangescheit on 9/30/17.
//

#include "ChessSaveWindow.h"
const int numOfSaveButtons = 7;

ChessButton** createSaveWindowChessButtons(SDL_Renderer *renderer) {
    if (renderer == NULL ) {
        return NULL ;
    }

    ChessButton** buttons = malloc(numOfSaveButtons * sizeof(ChessButton*));
    if (buttons == NULL ) {
        return NULL ;
    }

    SDL_Rect slot1 = { .x = 387, .y = 10, .h = 100, .w = 250 };
    SDL_Rect slot2 = { .x = 387, .y = 120, .h = 100, .w = 250 };
    SDL_Rect slot3 = { .x = 387, .y = 230, .h = 100, .w = 250 };
    SDL_Rect slot4 = { .x = 387, .y = 340, .h = 100, .w = 250 };
    SDL_Rect slot5 = { .x = 387, .y = 450, .h = 100, .w = 250 };
    SDL_Rect save = { .x = 200, .y = 650, .h = 100, .w = 250 };
    SDL_Rect back = { .x = 600, .y = 650, .h = 100, .w = 250 };


    buttons[0] = createChessButton(renderer, &slot1, "./assets/slot_1.bmp", "./assets/slot_1_inactive.bmp", CHESS_BUTTON_SLOT_1, false);
    buttons[1] = createChessButton(renderer, &slot2, "./assets/slot_2.bmp", "./assets/slot_2_inactive.bmp", CHESS_BUTTON_SLOT_2, false);
    buttons[2] = createChessButton(renderer, &slot3, "./assets/slot_3.bmp", "./assets/slot_3_inactive.bmp", CHESS_BUTTON_SLOT_3, false);
    buttons[3] = createChessButton(renderer, &slot4, "./assets/slot_4.bmp", "./assets/slot_4_inactive.bmp", CHESS_BUTTON_SLOT_4, false);
    buttons[4] = createChessButton(renderer, &slot5, "./assets/slot_5.bmp", "./assets/slot_5_inactive.bmp", CHESS_BUTTON_SLOT_5, false);
    buttons[5] = createChessButton(renderer, &save, "./assets/save_active.bmp", "./assets/save_active.bmp", CHESS_BUTTON_SAVE, false);
    buttons[6] = createChessButton(renderer, &back, "./assets/back_active.bmp", "./assets/back_active.bmp", CHESS_BUTTON_BACK, true);


    for (int i = 0; i < numOfSaveButtons ; i++) {
        if (buttons[i] == NULL) {
            destroySaveWindowButtons(buttons, numOfSaveButtons);
            return NULL;
        }
    }

    return buttons;
}
ChessSaveWindow * createSaveWindow() {
    ChessSaveWindow* res = malloc(sizeof(ChessSaveWindow));
    SDL_Window* window = SDL_CreateWindow("Tests", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    ChessButton** buttons = createSaveWindowChessButtons(renderer);
    if (res == NULL || window == NULL || renderer == NULL || buttons == NULL ) {
        free(res);
        free(buttons);
        //We first destroy the renderer
        SDL_DestroyRenderer(renderer); //NULL safe
        SDL_DestroyWindow(window); //NULL safe
        return NULL ;
    }
    res->buttons = buttons;
    res->numOfButtons = numOfSaveButtons;
    res->numSlots = 5;
    res->savePath = NULL;
    res->saveSlot = 0;
    res->window = window;
    res->windowRenderer = renderer;

    return res;
}

void destroySaveWindowButtons(ChessButton** buttons, int numOfButtons) {
    for (int i = 0; i < numOfButtons; i++) {
        destroyChessButton(buttons[i]);
    }

    free(buttons);
}

void drawSaveWindow(ChessSaveWindow *src) {
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

CHESS_SAVE_EVENT handleEventSaveWindow(ChessSaveWindow *src, SDL_Event *event){
    if(src == NULL || event==NULL){
        return CHESS_SAVE_INVALID_ARGUMENT;
    }

    for(int i = 0;i<src->numOfButtons;i++){
        BUTTON_CLICK_EVENT clickEvent = handleChessButtonEvent(src->buttons[i], event);
        switch (clickEvent) {
            case CHESS_CLICKED_SLOT_1:
                toggleSaveSlotButton(1, src, src->buttons[i]);
                return CHESS_SAVE_1;
            case CHESS_CLICKED_SLOT_2:
                toggleSaveSlotButton(2, src, src->buttons[i]);
                return CHESS_SAVE_2;
            case CHESS_CLICKED_SLOT_3:
                toggleSaveSlotButton(3, src, src->buttons[i]);
                return CHESS_SAVE_3;
            case CHESS_CLICKED_SLOT_4:
                toggleSaveSlotButton(4, src, src->buttons[i]);
                return CHESS_SAVE_4;
            case CHESS_CLICKED_SLOT_5:
                toggleSaveSlotButton(5, src, src->buttons[i]);
                return CHESS_SAVE_5;
            case CHESS_CLICKED_BACK:
                return CHESS_SAVE_BACK;
            case CHESS_CLICKED_SAVE:
                return CHESS_SAVE_APPLY;
            case CHESS_CLICKED_NEW_GAME:break;
            case CHESS_CLICKED_QUIT:break;
            case CHESS_CLICKED_NONE:break;
            case CHESS_CLICKED_1PLAYER:break;
            case CHESS_CLICKED_2PLAYER:break;
            case CHESS_CLICKED_NOOB:break;
            case CHESS_CLICKED_EASY:break;
            case CHESS_CLICKED_MODERATE:break;
            case CHESS_CLICKED_HARD:break;
            case CHESS_CLICKED_WHITE:break;
            case CHESS_CLICKED_BLACK:break;
            case CHESS_CLICKED_START:break;
            case CHESS_CLICKED_RESTART:break;
            case CHESS_CLICKED_LOAD:break;
            case CHESS_CLICKED_MAIN_MENU:break;
            case CHESS_CLICKED_UNDO:break;
        }
    }

    if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_CLOSE) return CHESS_SAVE_EXIT;

    return CHESS_SAVE_NONE;
}

void hideSaveWindow(ChessSaveWindow* src) {
    SDL_HideWindow(src->window);
}

void showSaveWindow(ChessSaveWindow* src) {
    SDL_ShowWindow(src->window);
}

void destroySaveWindow(ChessSaveWindow *src) {
    if (src == NULL ) {
        return;
    }

    for (int i = 0; i < src->numOfButtons; i++) {
        destroyChessButton(src->buttons[i]);
    }
    free(src->buttons);
    SDL_DestroyRenderer(src->windowRenderer);
    SDL_DestroyWindow(src->window);

    free(src);
}

void toggleSaveSlotButton(int selectedSlotNumber, ChessSaveWindow* src, ChessButton* button) {
    if (selectedSlotNumber > src->numSlots) return;
    if (src->saveSlot != selectedSlotNumber) {
        src->saveSlot = selectedSlotNumber;
//        sprintf(src->loadPath, "slot%d.xml", selectedSlotNumber);

        if (selectedSlotNumber == 1) {
            src->savePath = "slot1.xml ";
        }

        if (selectedSlotNumber == 2) {
            src->savePath = "slot2.xml ";
        }

        if (selectedSlotNumber == 3) {
            src->savePath = "slot3.xml ";
        }

        if (selectedSlotNumber == 4) {
            src->savePath = "slot4.xml ";
        }

        if (selectedSlotNumber == 5) {
            src->savePath = "slot5.xml ";
        }

        for (int j = 0;j<src->numSlots; j++) {
            if (src->buttons[j]->isActive) toggleChessButton(src->buttons[j]);
        }
        toggleChessButton(button);
    }
}