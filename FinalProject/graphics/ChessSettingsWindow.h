//
// Created by Jonathan Gescheit on 9/22/17.
//

#ifndef CHESS1_CHESSSETTINGSWINDOW_H
#define CHESS1_CHESSSETTINGSWINDOW_H

#include "ChessButton.h"
#include "ChessWindow.h"

typedef enum {
    CHESS_SETTINGS_DONE, CHESS_SETTINGS_BACK
} CHESS_SETTINGS_EVENT;

typedef struct chess_settings_window ChessSettingsWindow;
struct chess_settings_window {
    SDL_Window* window;
    SDL_Renderer* windowRenderer;
    ChessButton** buttons;
    int numOfButtons;
    GameSettings* settings;
};

ChessWindow* createSettingsWindow();
void destroySettingsWindow(ChessWindow* src);
void drawSettingsWindow(ChessWindow* src);
void hideSettingsWindow(ChessSettingsWindow* src);
void showSettingsWindow(ChessSettingsWindow* src);
CHESS_SETTINGS_EVENT handleEventSettingsWindow(ChessWindow* src, SDL_Event* event);

#endif //CHESS1_CHESSSETTINGSWINDOW_H
