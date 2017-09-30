//
// Created by Jonathan Gescheit on 9/22/17.
//

#ifndef CHESS1_CHESSBUTTON_H
#define CHESS1_CHESSBUTTON_H

#include <stdbool.h>
#include <SDL.h>
#include <SDL_video.h>
#include "ChessGUICommon.h"

typedef enum {
    CHESS_BUTTON_NEW_GAME, CHESS_BUTTON_LOAD, CHESS_BUTTON_QUIT,
    CHESS_BUTTON_1PLAYER, CHESS_BUTTON_2PLAYER,
    CHESS_BUTTON_NOOB, CHESS_BUTTON_EASY, CHESS_BUTTON_MODERATE, CHESS_BUTTON_HARD, CHESS_BUTTON_EXPERT,
    CHESS_BUTTON_WHITE, CHESS_BUTTON_BLACK,
    CHESS_BUTTON_BACK, CHESS_BUTTON_START,
    CHESS_BUTTON_RESTART, CHESS_BUTTON_SAVE, CHESS_BUTTON_MAIN_MENU, CHESS_BUTTON_UNDO
} ButtonType;

typedef enum {
    CHESS_CLICKED_NEW_GAME, CHESS_CLICKED_LOAD, CHESS_CLICKED_QUIT, CHESS_CLICKED_NONE,
    CHESS_CLICKED_1PLAYER, CHESS_CLICKED_2PLAYER,
    CHESS_CLICKED_NOOB, CHESS_CLICKED_EASY, CHESS_CLICKED_MODERATE, CHESS_CLICKED_HARD, CHESS_CLICKED_EXPERT,
    CHESS_CLICKED_WHITE, CHESS_CLICKED_BLACK,
    CHESS_CLICKED_BACK, CHESS_CLICKED_START,
    CHESS_CLICKED_RESTART, CHESS_CLICKED_SAVE, CHESS_CLICKED_MAIN_MENU, CHESS_CLICKED_UNDO
} BUTTON_CLICK_EVENT;

typedef struct chess_button{
    SDL_Texture* activeTexture;
    SDL_Texture* inactiveTexture;
    SDL_Renderer* windowRenderer;
    SDL_Rect* location;
    bool isActive;
    ButtonType type;
} ChessButton;

//You need a create function:
ChessButton* createChessButton(SDL_Renderer* windowRender, SDL_Rect* location, const char* activeImage, const char* inactiveImage, ButtonType type, bool isActive);

//You need this function in order to destroy all data Associate with a button:
void destroyChessButton(ChessButton*);

BUTTON_CLICK_EVENT handleChessButtonEvent(ChessButton *src, SDL_Event *event);

void drawChessButton(ChessButton* src);
void toggleChessButton(ChessButton* src);
void toggleDifficultyButton(ChessButton* src, int difficulty);

#endif //CHESS1_CHESSBUTTON_H
