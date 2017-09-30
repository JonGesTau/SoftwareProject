//
// Created by Jonathan Gescheit on 9/22/17.
//

#include "ChessGUIManager.h"

char* PIECES[] = {"pawn","bishop","knight","rook","queen","king"};

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
    res->loadWin = NULL;
    res->activeWin = CHESS_MAIN_WINDOW_ACTIVE;
    return res;
}
void chessManagerDestroy(ChessGuiManager *src) {
    if (!src) {
        return;
    }

    if (src->mainWin != NULL) destroyMainWindow(src->mainWin);
    if (src->settingsWin != NULL) destroySettingsWindow(src->settingsWin);
    if (src->gameWin != NULL) destroyGameWindow(src->gameWin);
    if (src->loadWin != NULL) destroyLoadWindow(src->loadWin);


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
    } else if (src->activeWin == CHESS_LOAD_WINDOW_ACTIVE) {
        drawLoadWindow(src->loadWin);
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
            showSettingsWindow(src->settingsWin);
        } else {
            src->settingsWin = createSettingsWindow();
        }

        src->activeWin = CHESS_SETTINGS_WINDOW_ACTIVE;
    }

    if (event == CHESS_MAIN_LOAD) {
        if (src->mainWin != NULL) {
            hideMainWindow(src->mainWin);
        } else {
            printf("No Main Window To Hide");
        }

        if (src->loadWin != NULL) {
            showLoadWindow(src->loadWin);
        } else {
            src->loadWin = createLoadWindow();
        }

        src->activeWin = CHESS_LOAD_WINDOW_ACTIVE;
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
            src->gameWin = createGameWindow(src->settingsWin->settings, NULL);
        }
        src->activeWin = CHESS_GAME_WINDOW_ACTIVE;
    }

    if (event == CHESS_SETTINGS_EXIT) {
        return CHESS_MANAGER_QUTT;
    }
    return CHESS_MANAGER_NONE;
}

CHESS_MANAGER_EVENT handleManagerDueToLoadEvent(ChessGuiManager* src, CHESS_LOAD_EVENT event) {
    if (src == NULL ) {
        return CHESS_MANAGER_NONE;
    }

    if (event == CHESS_LOAD_BACK) {
        if (src->loadWin != NULL) {
            hideLoadWindow(src->loadWin);
        } else {
            printf("No Load Win To Hide");
        }

        if (src->mainWin != NULL) {
            showMainWindow(src->mainWin);
        } else {
            printf("No Main Window To Show");
        }
        src->activeWin = CHESS_MAIN_WINDOW_ACTIVE;
    }

    if (event == CHESS_LOAD_APPLY) {
        GameState* loadGame = xmlGameLoadGame(src->loadWin->loadPath);
        if (loadGame == NULL) return CHESS_MANAGER_NONE;

        GameSettings* settings = GameSettingsCreate();
        setGameMode(settings, loadGame->mode);
        setDifficulty(settings, loadGame->difficulty);
        setUserColor(settings, loadGame->isPlayerWhite);

        hideLoadWindow(src->loadWin);

        if (src->gameWin != NULL) {
            destroyGameWindow(src->gameWin);
        }

        src->gameWin = NULL;
        src->gameWin = createGameWindow(settings, loadGame);
        src->activeWin = CHESS_GAME_WINDOW_ACTIVE;

        return CHESS_MANAGER_NONE;
    }

    if (event == CHESS_LOAD_EXIT) {
        return CHESS_MANAGER_QUTT;
    }
    return CHESS_MANAGER_NONE;
}

CHESS_MANAGER_EVENT handleManagerDueToGameEvent(ChessGuiManager* src, CHESS_GAME_EVENT event) {
    if (src == NULL) {
        return CHESS_MANAGER_NONE;
    }

    char msg[1024];

    if (event == CHESS_GAME_UNDO) {
        if (src->gameWin->settings->gameMode == 2) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Undo Unavailable", STR_ERR_UNDO_UNAVAILABLE, NULL);
        } else {
            HistoryMove* hist = GameStateGetLastMove(src->gameWin->game);
            if(hist == NULL) {
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Empty History", STR_ERR_EMPTY_HISTORY, NULL);
            } else {
                printf("Undo move for player %s : <%c,%c> -> <%c,%c>\n",
                       (src->gameWin->game->gameBoard->whiteTurn ? "black" : "white"),
                       (hist->move->y2 + '1'), (hist->move->x2 + 'A'), (hist->move->y1 + '1'),
                       (hist->move->x1 + 'A'));
                GameStateUndoHistoryMove(src->gameWin->game);
                hist = GameStateGetLastMove(src->gameWin->game);
                // TODO: make sure hist gets destroyed
                if(hist != NULL) {
                    printf("Undo move for player %s : <%c,%c> -> <%c,%c>\n",
                           (src->gameWin->game->gameBoard->whiteTurn ? "black" : "white"),
                           (hist->move->y2 + '1'), (hist->move->x2 + 'A'), (hist->move->y1 + '1'),
                           (hist->move->x1 + 'A'));
                    GameStateUndoHistoryMove(src->gameWin->game);
                    // TODO: what happens if player went first and then undos it all?
                }

                drawChessGamePieces(src->gameWin);
            }
        }
        return CHESS_MANAGER_NONE;
    }

    if (event == CHESS_GAME_MAIN_MENU) {
        showMainWindow(src->mainWin);
        src->activeWin = CHESS_MAIN_WINDOW_ACTIVE;
        if (src->settingsWin) {
            destroySettingsWindow(src->settingsWin);
            src->settingsWin = NULL;
        }
        if (src->gameWin) {
            destroyGameWindow(src->gameWin);
            src->gameWin = NULL;
        }
        return CHESS_MANAGER_NONE;
    }

    if (event == CHESS_GAME_RESTART) {
        destroyGameWindow(src->gameWin);
        src->gameWin = createGameWindow(src->settingsWin->settings, NULL);

        return CHESS_MANAGER_NONE;
    }

    if (src->gameWin->game->mode == 1 && (src->gameWin->game->gameBoard->whiteTurn != src->gameWin->game->isPlayerWhite)) {
        Move* compMove = miniMaxGetComputerMove(src->gameWin->game);
        printf("Computer: move %s at <%c,%c> to <%c,%c>\n",
               PIECES[(whichPiece(src->gameWin->game->gameBoard->board[compMove->y1][compMove->x1]))-1],
               (compMove->y1+'1'), (compMove->x1+'A'), (compMove->y2+'1'), (compMove->x2+'A'));

        GameStatePerformMove(src->gameWin->game, compMove->y1, compMove->x1, compMove->y2, compMove->x2);
        MoveDestroy(compMove);

        if(gameBoardIsStalemate(src->gameWin->game->gameBoard)){
            sprintf(msg, "The game is tied\n");
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Tie", msg, NULL);

            showMainWindow(src->mainWin);
            src->activeWin = CHESS_MAIN_WINDOW_ACTIVE;
            if (src->settingsWin) {
                destroySettingsWindow(src->settingsWin);
                src->settingsWin = NULL;
            }
            if (src->gameWin) {
                destroyGameWindow(src->gameWin);
                src->gameWin = NULL;
            }
            return CHESS_MANAGER_NONE;
        }
        if (gameBoardIsMate(src->gameWin->game->gameBoard, src->gameWin->game->gameBoard->whiteTurn)) {
            sprintf(msg, "Checkmate! %s player wins the game\n", COLOR(!src->gameWin->game->gameBoard->whiteTurn));
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Mate", msg, NULL);

            showMainWindow(src->mainWin);
            src->activeWin = CHESS_MAIN_WINDOW_ACTIVE;
            if (src->settingsWin) {
                destroySettingsWindow(src->settingsWin);
                src->settingsWin = NULL;
            }
            if (src->gameWin) {
                destroyGameWindow(src->gameWin);
                src->gameWin = NULL;
            }
            return CHESS_MANAGER_NONE;
        }

        if (gameBoardIsCheck(src->gameWin->game->gameBoard, src->gameWin->game->gameBoard->whiteTurn)) {
            drawChessGamePieces(src->gameWin);
            sprintf(msg, "Check: %s King is threatened!\n", COLOR(src->gameWin->game->gameBoard->whiteTurn));
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Check", msg, NULL);
        } else {
            drawChessGamePieces(src->gameWin);
        }
    } else {
        switch (event) {
            case CHESS_GAME_MOVE_SUCCESS:
            case CHESS_GAME_MOVE_FAIL:
                drawChessGamePieces(src->gameWin);
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
            case CHESS_GAME_INVALID:break;
            case CHESS_GAME_START:break;
            case CHESS_GAME_BACK:break;
            case CHESS_GAME_EXIT:break;
            case CHESS_GAME_NONE:break;
            case CHESS_GAME_UNDO:break;
            case CHESS_GAME_RESTART:break;
            case CHESS_GAME_LOAD:break;
            case CHESS_GAME_SAVE:break;
            case CHESS_GAME_MAIN_MENU:break;
        }
    }

    if (event == CHESS_GAME_EXIT) return CHESS_MANAGER_QUTT;

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
    } else if (src->activeWin == CHESS_LOAD_WINDOW_ACTIVE) {
        CHESS_LOAD_EVENT loadEvent = handleEventLoadWindow(src->loadWin, event);
        return handleManagerDueToLoadEvent(src, loadEvent);
    }
    return CHESS_MANAGER_NONE;
}