//
// Created by Jonathan Gescheit on 9/22/17.
//

#include "ChessGUIManager.h"
#include <stdio.h>
#include <stdlib.h>

ChessGuiManager* ChessManagerCreate() {
    ChessGuiManager* res = (ChessGuiManager*) malloc(sizeof(ChessGuiManager));
    if (res == NULL ) {
        return NULL ;
    }
    res->mainWin = createMainWindow();
    if (res->mainWin == NULL ) {
        free(res);
        return NULL ;
    }
//    res->gameWin = NULL;
    res->activeWin = CHESS_MAIN_WINDOW_ACTIVE;
    return res;
}
void ChessManagerDestroy(ChessGuiManager* src) {
    if (!src) {
        return;
    }
//    if (src->activeWin == CHESS_GAME_WINDOW_ACTIVE) {
//        spGameWindowDestroy(src->gameWin);
//    }
    destroyMainWindow(src->mainWin);
    free(src);
}
void ChessManagerDraw(ChessGuiManager* src) {
    if (!src) {
        return;
    }
    if (src->activeWin == CHESS_MAIN_WINDOW_ACTIVE) {
        drawMainWindow(src->mainWin);
    } else {
//        spGameWindowDraw(src->gameWin);
    }
}
CHESS_MANAGER_EVENT handleManagerDueToMainEvent(ChessGuiManager* src, CHESS_MAIN_EVENT event) {
    if (src == NULL ) {
        return CHESS_MANAGER_NONE;
    }
    if (event == CHESS_MAIN_START) {
        showMainWindow(src->mainWin);
//        src->gameWin = spGameWindowCreate();
//        if (src->gameWin == NULL ) {
//            printf("Couldn't create game window\n");
//            return CHESS_MANAGER_QUTT;
//        }
//        src->activeWin = CHESS_GAME_WINDOW_ACTIVE;
    }
    if (event == CHESS_MAIN_EXIT) {
        return CHESS_MANAGER_QUTT;
    }
    return CHESS_MANAGER_NONE;
}

//CHESS_MANAGER_EVENT handleManagerDueToGameEvent(ChessGuiManager* src, CHESS_GAME_EVENT event) {
//    if (event == CHESS_GAME_EVENT_NONE || src == NULL ) {
//        return CHESS_MANAGER_NONE;
//    }
//    if (event == CHESS_GAME_EVENT_X_WON) {
//        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "X won",
//                                 NULL );
//    } else if (event == CHESS_GAME_EVENT_O_WON) {
//        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "O won",
//                                 NULL );
//    } else if (event == CHESS_GAME_EVENT_TIE) {
//        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over",
//                                 "it's a tie", NULL );
//    }
//    spGameWindowDestroy(src->gameWin);
//    src->gameWin = NULL;
//    src->activeWin = CHESS_MAIN_WINDOW_ACTIVE;
//    spMainWindowShow(src->mainWin);
//    return CHESS_MANAGER_NONE;
//}

CHESS_MANAGER_EVENT ChessManagerHandleEvent(ChessGuiManager* src, SDL_Event* event) {
    if (src == NULL || event == NULL ) {
        return CHESS_MANAGER_NONE;
    }
    if (src->activeWin == CHESS_MAIN_WINDOW_ACTIVE) {
        CHESS_MAIN_EVENT mainEvent = handleEventMainWindow(src->mainWin, event);
        return handleManagerDueToMainEvent(src, mainEvent);
    } else {
//        CHESS_GAME_EVENT gameEvent = spGameWindowHandleEvent(src->gameWin, event);
//        spManagerDraw(src);
//        return handleManagerDueToGameEvent(src, gameEvent);
    }
    return CHESS_MANAGER_NONE;
}