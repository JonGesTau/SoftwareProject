//
// Created by Dror on 2017-08-19.
//

#include "GameState.h"

GameState* GameStateCreate(char difficulty, bool isPlayerWhite, char mode){
    GameState* game = malloc(sizeof(GameState));
    if(game == NULL){
        printf("ERROR");
        return NULL;
        // ERROR
    }

    game -> isPlayerWhite = isPlayerWhite;
    game ->mode = mode;
    game->difficulty = difficulty;
    game ->gameBoard = gameBoardCreate();
    gameBoardSetup(game -> gameBoard);

    // make sure history is all NULL
    for(int i = 0; i<MAX_UNDO*2; i++){
        game->history[i] = NULL;
    }

    return game;
}

void GameStateDestroy(GameState* game){
    if(game == NULL){
        // ERROR
        return;
    }
    if(game -> gameBoard != NULL)
        gameBoardDestroy(game->gameBoard);

    for(int i = 0; i<MAX_UNDO*2; i++){
        if(game->history[i] == NULL) break;
        HistoryMoveDestroy(game->history[i]);
    }

    free(game);
}

bool GameStatePerformMove(GameState* game, unsigned char y1, unsigned char x1, unsigned char y2, unsigned char x2){
    HistoryMove* hist = HistoryMoveCreate(y1, x1, y2, x2, game->gameBoard->board[y2][x2]);

    if(game->history[MAX_UNDO*2-1] != NULL){ // history full
        HistoryMoveDestroy(game->history[0]);
        for(unsigned char i = 0; i<(MAX_UNDO*2-1); i++){
            game->history[i] = game->history[i+1];
        }
        game->history[MAX_UNDO*2-1] = hist;
    } else { // not full, pick first open spot
        for(unsigned char i = 0; i<(MAX_UNDO*2); i++){
            if(game->history[i] == NULL){
                game->history[i] = hist;
                break;
            }
        }
    }

    gameBoardPerformMove(game->gameBoard, y1, x1, y2, x2);

    return true;
}

HistoryMove* GameStateGetLastMove(GameState* game){
    HistoryMove* hist = NULL;

    for(int i = MAX_UNDO*2-1; i>-1; i--){
        if(game->history[i] != NULL){
            hist = game->history[i];
            break;
        }
    }

    return hist;
}

void GameStateUndoHistoryMove(GameState* game){
    HistoryMove* hist = NULL;

    for(int i = MAX_UNDO*2-1; i>-1; i--){
        if(game->history[i] != NULL){
            hist = game->history[i];
            game->history[i] = NULL;
            break;
        }
    }

    gameBoardUndoMove(game->gameBoard, hist);
    HistoryMoveDestroy(hist);
}