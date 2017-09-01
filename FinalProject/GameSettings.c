//
// Created by Jonathan Gescheit on 9/1/17.
//

#include <stdlib.h>
#include <printf.h>
#include "GameSettings.h"

GameSettings* getDefaultSettings() {
    GameSettings* settings = malloc(sizeof(GameSettings));
    settings->gameMode = 1;
    settings->difficulty = 2;
    settings->userColor = 1;

    return settings;
}

void promptSelectSetting() {
    printf("Specify game setting or type 'start' to begin a game with the current setting:\n");
}

void setGameMode(GameSettings* settings, int value) {
    if (value < 1 || value > 2) {
        printf("Wrong game mode\n");
    } else {
        settings->gameMode = value;
        printf("Game mode is set to %d players\n", settings->gameMode);
    }
}

void setDifficulty(GameSettings* settings, int value) {
    if (settings->gameMode != 1) {
        printf("invalid command\n");
    } else if (value < 1 || value > 5) {
        printf("Wrong difficulty level. The value should be between 1 to 5\n");
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
        printf("DIFFICULTY: %d\n", settings->difficulty);
        printf("USER_CLR: %d\n", settings->userColor);
    }
}