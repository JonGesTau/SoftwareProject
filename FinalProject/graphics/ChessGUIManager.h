//
// Created by Jonathan Gescheit on 9/22/17.
//

// GUI Controller

#ifndef CHESS1_CHESSGUIMANAGER_H
#define CHESS1_CHESSGUIMANAGER_H

#include <SDL_events.h>
#include "ChessMainWindow.h"
#include "ChessSettingsWindow.h"
#include "ChessGameWindow.h"
#include "ChessLoadWindow.h"
#include "ChessSaveWindow.h"

/**
 * Represents which window is active
 */
typedef enum{
    CHESS_MAIN_WINDOW_ACTIVE,
    CHESS_GAME_WINDOW_ACTIVE,
    CHESS_SETTINGS_WINDOW_ACTIVE,
    CHESS_LOAD_WINDOW_ACTIVE,
    CHESS_SAVE_WINDOW_ACTIVE
}ACTIVE_WINDOW;

/**
 * Represents a manager event (mostly used for quitting)
 */
typedef enum{
    CHESS_MANAGER_QUTT,
    CHESS_MANAGER_NONE,
}CHESS_MANAGER_EVENT;

/**
 * Represents the controller itself
 */
typedef struct {
    ChessSettingsWindow* settingsWin;
    ChessMainWindow* mainWin;
    ChessGameWindow* gameWin;
    ChessLoadWindow* loadWin;
    ChessSaveWindow* saveWin;
    ACTIVE_WINDOW activeWin;
} ChessGuiManager;

/**
 * Create GUI manager
 * @return manager
 */
ChessGuiManager* ChessManagerCreate();

/**
 * Destroy GUI manager
 * @param src
 */
void chessManagerDestroy(ChessGuiManager *src);

/**
 * Draw on screen
 * @param src
 */
void chessManagerDraw(ChessGuiManager *src);

/**
 * Handle events from all windows (this is where specific handlers are triggered)
 * @param src
 * @param event
 * @return event
 */
CHESS_MANAGER_EVENT chessManagerHandleEvent(ChessGuiManager *src, SDL_Event *event);

/**
 * Handle events coming from the main window
 * @param src
 * @param event
 * @return event
 */
CHESS_MANAGER_EVENT handleManagerDueToMainEvent(ChessGuiManager* src, CHESS_MAIN_EVENT event);

/**
 * Handle events coming from the settings window
 * @param src
 * @param event
 * @return event
 */
CHESS_MANAGER_EVENT handleManagerDueToSettingsEvent(ChessGuiManager* src, CHESS_SETTINGS_EVENT event);

/**
 * Handle events coming from the load window
 * @param src
 * @param event
 * @return event
 */
CHESS_MANAGER_EVENT handleManagerDueToLoadEvent(ChessGuiManager* src, CHESS_LOAD_EVENT event);

/**
 * Handle events coming from the game window
 * @param src
 * @param event
 * @return event
 */
CHESS_MANAGER_EVENT handleManagerDueToGameEvent(ChessGuiManager* src, CHESS_GAME_EVENT event);

/**
 * Handle events coming from the save window
 * @param src
 * @param event
 * @return event
 */
CHESS_MANAGER_EVENT handleManagerDueToSaveEvent(ChessGuiManager* src, CHESS_SAVE_EVENT event);

#endif //CHESS1_CHESSGUIMANAGER_H
