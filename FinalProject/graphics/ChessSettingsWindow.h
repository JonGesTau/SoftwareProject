//
// Created by Jonathan Gescheit on 9/22/17.
//

// Settings window. Select game settings.

#ifndef CHESS1_CHESSSETTINGSWINDOW_H
#define CHESS1_CHESSSETTINGSWINDOW_H

#include "ChessButton.h"
#include "../GameSettings.h"

/**
 * Determine an event in the settings window
 */
typedef enum {
    CHESS_SETTINGS_START, CHESS_SETTINGS_BACK, CHESS_SETTINGS_EXIT, CHESS_SETTINGS_NONE
} CHESS_SETTINGS_EVENT;

/**
 * The settings window itself
 */
typedef struct chess_settings_window ChessSettingsWindow;
struct chess_settings_window {
    SDL_Window* window;
    SDL_Renderer* windowRenderer;
    ChessButton** buttons;
    int numOfButtons;
    GameSettings* settings;
};

/**
 * Create settings window
 * @return window
 */
ChessSettingsWindow* createSettingsWindow();

/**
 * Destroy settings window
 * @param src
 */
void destroySettingsWindow(ChessSettingsWindow *src);

/**
 * Draw settings window on screen
 * @param src
 */
void drawSettingsWindow(ChessSettingsWindow *src);

/**
 * Hide settings window
 * @param src
 */
void hideSettingsWindow(ChessSettingsWindow* src);

/**
 * Show settings window
 * @param src
 */
void showSettingsWindow(ChessSettingsWindow* src);

/**
 * Handle events in the settings window
 * @param src
 * @param event
 * @return event
 */
CHESS_SETTINGS_EVENT handleEventSettingsWindow(ChessSettingsWindow *src, SDL_Event *event);

/**
 * Create screen buttons
 * @param renderer
 * @param settings
 * @return buttons array
 */
ChessButton** createSettingsWindowChessButtons(SDL_Renderer *renderer, GameSettings *settings);

/**
 * Destroy screen buttons
 * @param buttons
 * @param numOfButtons
 */
void destroySettingsWindowButtons(ChessButton** buttons, int numOfButtons);

#endif //CHESS1_CHESSSETTINGSWINDOW_H
