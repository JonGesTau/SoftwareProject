//
// Created by Jonathan Gescheit on 9/22/17.
//

#ifndef CHESS1_CHESSSETTINGSWINDOW_H
#define CHESS1_CHESSSETTINGSWINDOW_H

#include "ChessButton.h"
#include "../GameSettings.h"

typedef enum {
    CHESS_SETTINGS_START, CHESS_SETTINGS_BACK, CHESS_SETTINGS_EXIT
} CHESS_SETTINGS_EVENT;

typedef struct chess_settings_window ChessSettingsWindow;
struct chess_settings_window {
    SDL_Window* window;
    SDL_Renderer* windowRenderer;
    ChessButton** buttons;
    int numOfButtons;
    GameSettings* settings;
};

ChessSettingsWindow* createSettingsWindow();
void destroySettingsWindow(ChessSettingsWindow *src);
void drawSettingsWindow(ChessSettingsWindow *src);
void hideSettingsWindow(ChessSettingsWindow* src);
void showSettingsWindow(ChessSettingsWindow* src);
CHESS_SETTINGS_EVENT handleEventSettingsWindow(ChessSettingsWindow *src, SDL_Event *event);
ChessButton** createSettingsWindowChessButtons(SDL_Renderer *renderer, GameSettings *settings);

#endif //CHESS1_CHESSSETTINGSWINDOW_H
