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
    gameBoardSetup(game -> gameBoard, true);
    return game;
}

void GameStateDestroy(GameState* game){
    if(game == NULL){
        // ERROR
        return;
    }
    if(game -> gameBoard != NULL)
        gameBoardDestroy(game->gameBoard);

    free(game);
}