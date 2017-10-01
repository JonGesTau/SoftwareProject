//
// Created by Jonathan Gescheit on 9/22/17.
//

#ifndef CHESS1_CHESSGUIMANAGER_H
#define CHESS1_CHESSGUIMANAGER_H

#include <SDL_events.h>
#include "ChessMainWindow.h"
#include "ChessSettingsWindow.h"
#include "ChessGameWindow.h"
#include "ChessLoadWindow.h"
#include "ChessSaveWindow.h"

typedef enum{
    CHESS_MAIN_WINDOW_ACTIVE,
    CHESS_GAME_WINDOW_ACTIVE,
    CHESS_SETTINGS_WINDOW_ACTIVE,
    CHESS_LOAD_WINDOW_ACTIVE,
    CHESS_SAVE_WINDOW_ACTIVE
}ACTIVE_WINDOW;

typedef enum{
    CHESS_MANAGER_QUTT,
    CHESS_MANAGER_NONE,
}CHESS_MANAGER_EVENT;

typedef struct {
//    ChessGameWindow* gameWin;
    ChessSettingsWindow* settingsWin;
    ChessMainWindow* mainWin;
    ChessGameWindow* gameWin;
    ChessLoadWindow* loadWin;
    ChessSaveWindow* saveWin;
    ACTIVE_WINDOW activeWin;
} ChessGuiManager;

ChessGuiManager* ChessManagerCreate();

void chessManagerDestroy(ChessGuiManager *src);

void chessManagerDraw(ChessGuiManager *src);

CHESS_MANAGER_EVENT chessManagerHandleEvent(ChessGuiManager *src, SDL_Event *event);
CHESS_MANAGER_EVENT handleManagerDueToMainEvent(ChessGuiManager* src, CHESS_MAIN_EVENT event);
CHESS_MANAGER_EVENT handleManagerDueToSettingsEvent(ChessGuiManager* src, CHESS_SETTINGS_EVENT event);
CHESS_MANAGER_EVENT handleManagerDueToLoadEvent(ChessGuiManager* src, CHESS_LOAD_EVENT event);
CHESS_MANAGER_EVENT handleManagerDueToGameEvent(ChessGuiManager* src, CHESS_GAME_EVENT event);
CHESS_MANAGER_EVENT handleManagerDueToSaveEvent(ChessGuiManager* src, CHESS_SAVE_EVENT event);

#endif //CHESS1_CHESSGUIMANAGER_H
