//
// Created by Jonathan Gescheit on 9/22/17.
//

#include "ChessGUIManager.h"

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
    res->gameWin = NULL;
    res->settingsWin = NULL;
    res->activeWin = CHESS_MAIN_WINDOW_ACTIVE;
    return res;
}
void chessManagerDestroy(ChessGuiManager *src) {
    if (!src) {
        return;
    }
    if (src->activeWin == CHESS_GAME_WINDOW_ACTIVE) {
        destroyGameWindow(src->gameWin);
    }
    if (src->activeWin == CHESS_SETTINGS_WINDOW_ACTIVE) {
        destroySettingsWindow(src->settingsWin);
    }
    if (src->activeWin == CHESS_GAME_WINDOW_ACTIVE) {
        destroyGameWindow(src->gameWin);
    }
    destroyMainWindow(src->mainWin);
    free(src);
}
void chessManagerDraw(ChessGuiManager *src) {
    if (!src) {
        return;
    }
    if (src->activeWin == CHESS_MAIN_WINDOW_ACTIVE) {
        drawMainWindow(src->mainWin);
    } else if (src->activeWin == CHESS_GAME_WINDOW_ACTIVE) {
        drawGameWindow(src->gameWin);
    } else if (src->activeWin == CHESS_SETTINGS_WINDOW_ACTIVE) {
        drawSettingsWindow(src->settingsWin);
    }
}
CHESS_MANAGER_EVENT handleManagerDueToMainEvent(ChessGuiManager* src, CHESS_MAIN_EVENT event) {
    if (src == NULL ) {
        return CHESS_MANAGER_NONE;
    }
    if (event == CHESS_MAIN_START) {
        if (src->mainWin != NULL) {
            hideMainWindow(src->mainWin);
        } else {
            printf("No Main Window To Hide");
        }

        if (src->settingsWin != NULL) {
            hideSettingsWindow(src->settingsWin);
        } else {
            src->settingsWin = createSettingsWindow();
        }

        src->activeWin = CHESS_SETTINGS_WINDOW_ACTIVE;
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

CHESS_MANAGER_EVENT handleManagerDueToSettingsEvent(ChessGuiManager* src, CHESS_SETTINGS_EVENT event) {
    if (src == NULL ) {
        return CHESS_MANAGER_NONE;
    }
    if (event == CHESS_MAIN_START) {
        if (src->mainWin != NULL) {
            showMainWindow(src->mainWin);
        } else {
            printf("No Main Window To Show");
        }
//        src->gameWin = spGameWindowCreate();
//        if (src->gameWin == NULL ) {
//            printf("Couldn't create game window\n");
//            return CHESS_MANAGER_QUTT;
//        }
//        src->activeWin = CHESS_GAME_WINDOW_ACTIVE;
    }
    if (event == CHESS_SETTINGS_BACK) {
        if (src->settingsWin != NULL) {
            hideSettingsWindow(src->settingsWin);
        } else {
            printf("No Settings Win To Hide");
        }

        if (src->mainWin != NULL) {
            showMainWindow(src->mainWin);
        } else {
            printf("No Main Window To Show");
        }
        src->activeWin = CHESS_MAIN_WINDOW_ACTIVE;
    }

    if (event == CHESS_SETTINGS_START) {
        if (src->settingsWin != NULL) {
            hideSettingsWindow(src->settingsWin);
        } else {
            printf("No Settings Win To Hide");
        }

        if (src->gameWin!= NULL) {
            hideSettingsWindow(src->settingsWin);
        } else {
            src->gameWin = createGameWindow();
        }
        src->activeWin = CHESS_GAME_WINDOW_ACTIVE;
    }

    if (event == CHESS_SETTINGS_EXIT) {
        return CHESS_MANAGER_QUTT;
    }
    return CHESS_MANAGER_NONE;
}

CHESS_MANAGER_EVENT handleManagerDueToGameEvent(ChessGuiManager* src, CHESS_GAME_EVENT event) {
    if (src == NULL) {
        return CHESS_MANAGER_NONE;
    }

    char msg[1024];

    switch (event) {
        case CHESS_GAME_MOVE_SUCCESS:
        case CHESS_GAME_MOVE_FAIL:
            drawChessGamePieces(src->gameWin);
//            free(msg);
            break;
        case CHESS_GAME_CHECK:
            drawChessGamePieces(src->gameWin);
            sprintf(msg, "Check: %s King is threatened!\n", COLOR(src->gameWin->game->gameBoard->whiteTurn));
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Check", msg, NULL);
            break;
        case CHESS_GAME_MATE:
            sprintf(msg, "Checkmate! %s player wins the game\n", COLOR(!src->gameWin->game->gameBoard->whiteTurn));
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Mate", msg, NULL);
            GameStateDestroy(src->gameWin->game);
            break;
        case CHESS_GAME_STALEMATE:
            sprintf(msg, "The game is tied\n");
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Tie", msg, NULL);
            GameStateDestroy(src->gameWin->game);
            break;
    }

    return CHESS_MANAGER_NONE;
}

CHESS_MANAGER_EVENT chessManagerHandleEvent(ChessGuiManager *src, SDL_Event *event) {
    if (src == NULL || event == NULL ) {
        return CHESS_MANAGER_NONE;
    }
    if (src->activeWin == CHESS_MAIN_WINDOW_ACTIVE) {
        CHESS_MAIN_EVENT mainEvent = handleEventMainWindow(src->mainWin, event);
        return handleManagerDueToMainEvent(src, mainEvent);
    } else if (src->activeWin == CHESS_GAME_WINDOW_ACTIVE) {
        CHESS_GAME_EVENT gameEvent = handleEventGameWindow(src->gameWin, event);
        return handleManagerDueToGameEvent(src, gameEvent);
    } else if (src->activeWin == CHESS_SETTINGS_WINDOW_ACTIVE) {
        CHESS_SETTINGS_EVENT settingsEvent = handleEventSettingsWindow(src->settingsWin, event);
        return handleManagerDueToSettingsEvent(src, settingsEvent);
    }
    return CHESS_MANAGER_NONE;
}