//
// Created by Jonathan Gescheit on 9/1/17.
//

#ifndef CHESS1_GAMESETTINGS_H
#define CHESS1_GAMESETTINGS_H

#include <stdlib.h>
#include <stdio.h>
#include "MainAux.h"

/**
 * This data structure binds the game settings data during the game setup mode.
 * gameMode - 1 or 2 for 1- or 2- player mode.
 * difficulty - 1 to 4.
 * userColor - 0 or 1 for black or white.
 */
typedef struct chess_gamesettings {
    int gameMode;
    int difficulty;
    int userColor;
} GameSettings;

/**
 * Allocates a GameSettings object with the default settings.
 * @return a pointer to the new object.
 */
GameSettings* GameSettingsCreate();

/**
 * Frees from memory a GameSettings object.
 * @param settings - the object to free.
 */
void GameSettingsDestroy(GameSettings* settings);

/**
 * Given a GameSettings object, sets its data to the default settings.
 * @param settings - the object to change.
 */
void setDefaultSettings(GameSettings* settings);

/**
 * Sets the gameMode parameter.
 * @param settings - the object to change.
 * @param value - the new value for gameMode.
 */
void setGameMode(GameSettings* settings, int value);

/**
 * Sets the difficulty parameter.
 * @param settings - the object to change.
 * @param value - the new value for difficulty.
 */
void setDifficulty(GameSettings* settings, int value);

/**
 * Sets the userColor parameter.
 * @param settings - the object to change.
 * @param value - the new value for userColor.
 */
void setUserColor(GameSettings* settings, int value);

/**
 * Prints the given settings to the console according to the appropriate formats.
 */
void printSettings(GameSettings*);

#endif //CHESS1_GAMESETTINGS_H
