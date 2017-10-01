//
// Created by jonathangescheit on 9/30/17.
//

// Save game to one of 5 predetermined slots.

#ifndef CHESS1_CHESSSAVEWINDOW_H
#define CHESS1_CHESSSAVEWINDOW_H
#include "ChessButton.h"
#include "../xmlGame.h"

/**
 * Determine an event in the save window
 */
typedef enum {
    CHESS_SAVE_1, CHESS_SAVE_2, CHESS_SAVE_3, CHESS_SAVE_4, CHESS_SAVE_5, CHESS_SAVE_BACK, CHESS_SAVE_INVALID_ARGUMENT, CHESS_SAVE_APPLY, CHESS_SAVE_NONE, CHESS_SAVE_EXIT
} CHESS_SAVE_EVENT;

/**
 * The save window itself
 */
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

/**
 * Create save window
 * @return window
 */
ChessSaveWindow * createSaveWindow();

/**
 * Destroy save window
 * @param buttons
 * @param numOfButtons
 */
void destroySaveWindowButtons(ChessButton** buttons, int numOfButtons);

/**
 * Draw save window on screen
 * @param src
 */
void drawSaveWindow(ChessSaveWindow *src);

/**
 * Hide save window
 * @param src
 */
void hideSaveWindow(ChessSaveWindow* src);

/**
 * Show save window
 * @param src
 */
void showSaveWindow(ChessSaveWindow* src);

/**
 * Handle events in the save window
 * @param src
 * @param event
 * @return event
 */
CHESS_SAVE_EVENT handleEventSaveWindow(ChessSaveWindow *src, SDL_Event *event);

/**
 * Destroy save window
 * @param src
 */
void destroySaveWindow(ChessSaveWindow *src);

/**
 * Toggle a slot button
 * @param selectedSlotNumber
 * @param src
 * @param button
 */
void toggleSaveSlotButton(int selectedSlotNumber, ChessSaveWindow* src, ChessButton* button);

#endif //CHESS1_CHESSSAVEWINDOW_H
