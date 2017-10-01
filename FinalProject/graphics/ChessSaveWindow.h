//
// Created by jonathangescheit on 9/30/17.
//

#ifndef CHESS1_CHESSSAVEWINDOW_H
#define CHESS1_CHESSSAVEWINDOW_H
#include "ChessButton.h"
#include "../xmlGame.h"

typedef enum {
    CHESS_SAVE_1, CHESS_SAVE_2, CHESS_SAVE_3, CHESS_SAVE_4, CHESS_SAVE_5, CHESS_SAVE_BACK, CHESS_SAVE_INVALID_ARGUMENT, CHESS_SAVE_APPLY, CHESS_SAVE_NONE, CHESS_SAVE_EXIT
} CHESS_SAVE_EVENT;

typedef struct chess_save_window ChessSaveWindow;
struct chess_save_window {
    SDL_Window* window;
    SDL_Renderer* windowRenderer;
    ChessButton** buttons;
    int numOfButtons;
    char* savePath;
    int saveSlot;
    int numSlots;
};

ChessSaveWindow * createSaveWindow();
void destroySaveWindowButtons(ChessButton** buttons, int numOfButtons);
void drawSaveWindow(ChessSaveWindow *src);
void hideSaveWindow(ChessSaveWindow* src);
void showSaveWindow(ChessSaveWindow* src);
CHESS_SAVE_EVENT handleEventSaveWindow(ChessSaveWindow *src, SDL_Event *event);
void destroySaveWindow(ChessSaveWindow *src);
void toggleSaveSlotButton(int selectedSlotNumber, ChessSaveWindow* src, ChessButton* button);
#endif //CHESS1_CHESSSAVEWINDOW_H
