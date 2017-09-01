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
void setGameMode();
void setDifficulty();
void setUserColor();
void printSettings(GameSettings*);
GameSettings* getDefaultSettings();


#endif //CHESS1_GAMESETTINGS_H
