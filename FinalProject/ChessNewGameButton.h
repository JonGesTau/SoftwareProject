//
// Created by Jonathan Gescheit on 9/22/17.
//

#ifndef CHESS1_CHESSNEWGAMEBUTTON_H
#define CHESS1_CHESSNEWGAMEBUTTON_H

#include <stdbool.h>
#include "ChessWidget.h" //A button is a widget also

typedef struct chess_new_game_button ChessNewGameButton;
struct chess_new_game_button{
    SDL_Texture* buttonTexture;
    SDL_Renderer* windowRenderer;
    SDL_Rect* location;
    bool isActive;
};

//You need a create function:
ChessWidget* createChessNewGameButton(SDL_Renderer* windowRender, SDL_Rect* location,
                           const char* image);

//You need this function in order to destroy all data Associate with a button:
void destroyChessNewGameButton(ChessWidget*);

void handleChessNewGameButtonEvenet(ChessWidget* src, SDL_Event* event);

void drawChessNewGameButton(ChessWidget* src);

#endif //CHESS1_CHESSNEWGAMEBUTTON_H
