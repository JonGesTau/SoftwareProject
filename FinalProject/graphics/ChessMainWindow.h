//
// Created by Jonathan Gescheit on 9/22/17.
//

// Main menu window. Start a new game, load game or quit.

#ifndef CHESS1_CHESSMAINWINDOW_H
#define CHESS1_CHESSMAINWINDOW_H

#include "ChessButton.h"

/**
 * Represents an event in the main menu
 */
typedef enum {
    CHESS_MAIN_EXIT, CHESS_MAIN_START, CHESS_MAIN_INVALID_ARGUMENT, CHESS_MAIN_NONE, CHESS_MAIN_LOAD
} CHESS_MAIN_EVENT;

/**
 * The main window itself
 */
typedef struct chess_main_window ChessMainWindow;
struct chess_main_window {
    SDL_Window* window;
    SDL_Renderer* windowRenderer;
    ChessButton** buttons;
    int numOfButtons;
};

/**
 * Create main window
 * @return
 */
ChessMainWindow * createMainWindow();

/**
 * Destroy main window
 * @param src
 */
void destroyMainWindow(ChessMainWindow *src);

/**
 * Draw main window on screen
 * @param src
 */
void drawMainWindow(ChessMainWindow *src);

/**
 * Hide main window
 * @param src
 */
void hideMainWindow(ChessMainWindow* src);

/**
 * Show main window
 * @param src
 */
void showMainWindow(ChessMainWindow* src);

/**
 * Handle events in the main window
 * @param src
 * @param event
 * @return event
 */
CHESS_MAIN_EVENT handleEventMainWindow(ChessMainWindow *src, SDL_Event *event);

#endif //CHESS1_CHESSMAINWINDOW_H
