//
// Created by Jonathan Gescheit on 9/22/17.
//

#ifndef CHESS1_CHESSMAINWINDOW_H
#define CHESS1_CHESSMAINWINDOW_H

#include "ChessButton.h"

typedef enum {
    CHESS_MAIN_EXIT, CHESS_MAIN_START, CHESS_MAIN_INVALID_ARGUMENT, CHESS_MAIN_NONE, CHESS_MAIN_LOAD
} CHESS_MAIN_EVENT;

typedef struct chess_main_window ChessMainWindow;
struct chess_main_window {
    SDL_Window* window;
    SDL_Renderer* windowRenderer;
    ChessButton** buttons;
    int numOfButtons;
};

ChessMainWindow * createMainWindow();
void destroyMainWindow(ChessMainWindow *src);
void drawMainWindow(ChessMainWindow *src);
void hideMainWindow(ChessMainWindow* src);
void showMainWindow(ChessMainWindow* src);
CHESS_MAIN_EVENT handleEventMainWindow(ChessMainWindow *src, SDL_Event *event);

#endif //CHESS1_CHESSMAINWINDOW_H
