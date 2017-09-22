//
// Created by Jonathan Gescheit on 9/22/17.
//

#ifndef CHESS1_CHESSBUTTON_H
#define CHESS1_CHESSBUTTON_H

#include <stdbool.h>
#include <SDL.h>

typedef enum {
    CHESS_BUTTON_NEW_GAME, CHESS_BUTTON_LOAD, CHESS_BUTTON_QUIT
} ButtonType;

typedef enum {
    CHESS_CLICKED_NEW_GAME, CHESS_CLICKED_LOAD, CHESS_CLICKED_QUIT, CHESS_CLICKED_NONE
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
ChessButton* createChessButton(SDL_Renderer* windowRender, SDL_Rect* location, const char* image, ButtonType type);

//You need this function in order to destroy all data Associate with a button:
void destroyChessButton(ChessButton*);

BUTTON_CLICK_EVENT handleChessButtonEvent(ChessButton *src, SDL_Event *event);

void drawChessButton(ChessButton* src);

#endif //CHESS1_CHESSBUTTON_H
