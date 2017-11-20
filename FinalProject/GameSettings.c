//
// Created by Jonathan Gescheit on 9/1/17.
//

#include "GameSettings.h"

GameSettings* GameSettingsCreate(){
    GameSettings* settings = malloc(sizeof(GameSettings));
    if(settings == NULL){
        // ERROR
        return NULL;
    }
    setDefaultSettings(settings);
    return settings;
}

void GameSettingsDestroy(GameSettings* settings){
    free(settings);
}

void setDefaultSettings(GameSettings* settings){
    settings->gameMode = 1;
    settings->difficulty = 2;
    settings->userColor = 1;
}

void setGameMode(GameSettings* settings, int value) {
    if (value < 1 || value > 2) {
        printf("Wrong game mode\n");
    } else {
        settings->gameMode = value;
        printf(settings->gameMode == 1 ? "Game mode is set to %d player\n" : "Game mode is set to %d players\n", settings->gameMode);
    }
}

void setDifficulty(GameSettings* settings, int value) {
    if (settings->gameMode != 1) {
        printf("invalid command\n");
    } else if (value < 1 || value > 5) {
        printf("Wrong difficulty level. The value should be between 1 to 5\n");
    } else if(value == 5 && !EXPERT_LEVEL_SUPPORTED) {
        printf("Expert level not supported, please choose a value between 1 to 4:\n");
    } else {
        settings->difficulty = value;
    }
}

void setUserColor(GameSettings* settings, int value) {
    if (settings->gameMode != 1) {
        printf("invalid command\n");
    } else if (value < 0 || value > 1) {
        printf("Wrong color\n");
    } else {
        settings->userColor = value;
    }
}

void printSettings(GameSettings* settings) {
    printf("SETTINGS:\n");
    printf("GAME_MODE: %d\n", settings->gameMode);

    if (settings->gameMode == 1) {
        printf("DIFFICULTY_LVL: %d\n", settings->difficulty);
        printf("USER_CLR: %s\n", settings->userColor ? "WHITE" : "BLACK");
    }
}