//
// Created by Jonathan Gescheit on 9/22/17.
//

#ifndef CHESS1_CHESSGUIMANAGER_H
#define CHESS1_CHESSGUIMANAGER_H

#include <SDL_events.h>
#include "ChessMainWindow.h"

typedef enum{
    CHESS_MAIN_WINDOW_ACTIVE,
    CHESS_GAME_WINDOW_ACTIVE
}ACTIVE_WINDOW;

typedef enum{
    CHESS_MANAGER_QUTT,
    CHESS_MANAGER_NONE,
}CHESS_MANAGER_EVENT;

typedef struct {
//    ChessGameWindow* gameWin;
    ChessMainWindow* mainWin;
    ACTIVE_WINDOW activeWin;
} ChessGuiManager;

ChessGuiManager* ChessManagerCreate();

void ChessManagerDestroy(ChessGuiManager* src);

void ChessManagerDraw(ChessGuiManager* src);

CHESS_MANAGER_EVENT ChessManagerHandleEvent(ChessGuiManager* src, SDL_Event* event) ;

#endif //CHESS1_CHESSGUIMANAGER_H
