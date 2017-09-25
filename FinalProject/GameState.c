//
// Created by Dror on 2017-08-19.
//

#include "GameState.h"

GameState* GameStateCreate(char difficulty, bool isPlayerWhite, bool mode){
    GameState* game = malloc(sizeof(GameState));
    if(game == NULL){
        // ERROR
    }
    game -> isPlayerWhite = isPlayerWhite;
    game ->mode = mode;
    game->difficulty = difficulty;
    game ->gameBoard = gameBoardCreate();
    // make sure history is all NULL
    for(int i = 0; i<MAX_UNDO*2; i++){
        game->history[i] = NULL;
    }
    gameBoardSetup(game -> gameBoard);
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

bool GameStatePerformMove(GameState* game, char y1, char x1, char y2, char x2){
    //if(!gameBoardIsLegalMove(game->gameBoard, y1, x1, y2, x2)) return false;
    // TODO: since we need to remember computer moves as well, the AI result also should come here
    // so maybe we can skip the legality check and put it in a higher level?

    HistoryMove* hist = HistoryMoveCreate(y1, x1, y2, x2, game->gameBoard->board[y2][x2]);
    // TODO: move memory errors into Creators

    if(game->history[MAX_UNDO*2-1] != NULL){ // history full
        HistoryMoveDestroy(game->history[0]);
        for(char i = 0; i<(MAX_UNDO*2-1); i++){
            game->history[i] = game->history[i+1];
        }
        game->history[MAX_UNDO*2-1] = hist;
    } else { // not full, pick first open spot
        for(char i = 0; i<(MAX_UNDO*2); i++){
            if(game->history[i] == NULL){
                game->history[i] = hist;
                break;
            }
        }
    }

    gameBoardPerformMove(game->gameBoard, y1, x1, y2, x2);
    game->current_move ++;

    return true;
}

bool GameStateUndoMove(GameState* game){
    HistoryMove* hist;

    for(char i = MAX_UNDO*2-1; i>-1; i++){
        if(game->history[i] != NULL){
            hist = game->history[i];
            break;
        }
    }

    if(hist == NULL) return false;

    gameBoardUndoMove(game->gameBoard, hist);
    game->current_move--;

    return true;
}