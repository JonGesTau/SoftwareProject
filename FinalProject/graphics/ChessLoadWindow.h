//
// Created by jonathangescheit on 9/30/17.
//

// Load game window. Select from 5 predetermined slots.

#ifndef CHESS1_CHESSLOADWINDOW_H
#define CHESS1_CHESSLOADWINDOW_H

#include "ChessButton.h"
#include "../xmlGame.h"

/**
 * Represents an event in the load window
 */
typedef enum {
    CHESS_LOAD_1, CHESS_LOAD_2, CHESS_LOAD_3, CHESS_LOAD_4, CHESS_LOAD_5, CHESS_LOAD_BACK, CHESS_LOAD_INVALID_ARGUMENT, CHESS_LOAD_APPLY, CHESS_LOAD_NONE, CHESS_LOAD_EXIT
} CHESS_LOAD_EVENT;

/**
 * Represents the load window itself
 */
typedef struct chess_load_window ChessLoadWindow;
struct chess_load_window {
    SDL_Window* window;
    SDL_Renderer* windowRenderer;
    ChessButton** buttons;
    int numOfButtons;
    char* loadPath;
    int loadSlot;
    int numSlots;
};

/**
 * Create load window
 * @return window
 */
ChessLoadWindow * createLoadWindow();

/**
 * Destroy load window
 * @param buttons
 * @param numOfButtons
 */
void destroyLoadWindowButtons(ChessButton** buttons, int numOfButtons);

/**
 * Draw load window on screen
 * @param src
 */
void drawLoadWindow(ChessLoadWindow *src);

/**
 * Hide load window
 * @param src
 */
void hideLoadWindow(ChessLoadWindow* src);

/**
 * Show load window
 * @param src
 */
void showLoadWindow(ChessLoadWindow* src);

/**
 * Handle events in the load window
 * @param src
 * @param event
 * @return event
 */
CHESS_LOAD_EVENT handleEventLoadWindow(ChessLoadWindow *src, SDL_Event *event);

/**
 * Destroy load window
 * @param src
 */
void destroyLoadWindow(ChessLoadWindow *src);

/**
 * Toggle a slot button
 * @param selectedSlotNumber
 * @param src
 * @param button
 */
void toggleSlotButton(int selectedSlotNumber, ChessLoadWindow* src, ChessButton* button);

#endif //CHESS1_CHESSLOADWINDOW_H
