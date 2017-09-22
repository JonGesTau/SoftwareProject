//
// Created by Jonathan Gescheit on 9/22/17.
//

#ifndef CHESS1_CHESSMAINWINDOW_H
#define CHESS1_CHESSMAINWINDOW_H

#include "ChessWindow.h"
#include "ChessWidget.h"

typedef struct chess_main_window ChessMainWindow;
struct chess_main_window {
    SDL_Window* window;
    SDL_Renderer* windowRenderer;
    //All widgets in our window
    ChessWidget** widgets;
    int numOfWidgets;
};

ChessWindow* createMainWindow();
void destroyMainWindow(ChessWindow* src);
void drawMainWindow(ChessWindow* src);
void handleEvenetMainWindow(ChessWindow* src, SDL_Event* event);

#endif //CHESS1_CHESSMAINWINDOW_H
