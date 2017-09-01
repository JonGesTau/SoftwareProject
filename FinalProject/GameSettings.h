//
// Created by Jonathan Gescheit on 9/1/17.
//

#ifndef CHESS1_GAMESETTINGS_H
#define CHESS1_GAMESETTINGS_H

typedef struct chess_gamesettings {
    int gameMode;
    int difficulty;
    int userColor;
} GameSettings;

void promptSelectSetting();
void setGameMode(GameSettings* settings, int value);
void setDifficulty(GameSettings* settings, int value);
void setUserColor(GameSettings* settings, int value);
void printSettings(GameSettings*);
GameSettings* getDefaultSettings();


#endif //CHESS1_GAMESETTINGS_H
