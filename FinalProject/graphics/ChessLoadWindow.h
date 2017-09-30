//
// Created by jonathangescheit on 9/30/17.
//

#ifndef CHESS1_CHESSLOADWINDOW_H
#define CHESS1_CHESSLOADWINDOW_H

#include "ChessButton.h"

typedef enum {
    CHESS_LOAD_1, CHESS_LOAD_2, CHESS_LOAD_3, CHESS_LOAD_4, CHESS_LOAD_5, CHESS_LOAD_BACK, CHESS_LOAD_INVALID_ARGUMENT, CHESS_LOAD_APPLY, CHESS_LOAD_NONE, CHESS_LOAD_EXIT
} CHESS_LOAD_EVENT;

typedef struct chess_load_window ChessLoadWindow;
struct chess_load_window {
    SDL_Window* window;
    SDL_Renderer* windowRenderer;
    ChessButton** buttons;
    int numOfButtons;
    char* loadPath;
    int loadSlot;
};

ChessLoadWindow * createLoadWindow();
void destroyLoadWindowButtons(ChessButton** buttons, int numOfButtons);
void drawLoadWindow(ChessLoadWindow *src);
void hideLoadWindow(ChessLoadWindow* src);
void showLoadWindow(ChessLoadWindow* src);
CHESS_LOAD_EVENT handleEventLoadWindow(ChessLoadWindow *src, SDL_Event *event);
void destroyLoadWindow(ChessLoadWindow *src);

#endif //CHESS1_CHESSLOADWINDOW_H
