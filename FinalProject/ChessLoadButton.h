//
// Created by Jonathan Gescheit on 9/22/17.
//

#ifndef CHESS1_CHESSLOADBUTTON_H
#define CHESS1_CHESSLOADBUTTON_H

#include "ChessWidget.h" //A button is a widget also

typedef struct chess_load_button ChessLoadButton;
struct chess_load_button{
    SDL_Texture* buttonTexture;
    SDL_Renderer* windowRenderer;
    SDL_Rect* location;
};

//You need a create function:
ChessWidget* createChessLoadButton(SDL_Renderer* windowRender, SDL_Rect* location,
                                      const char* image);

//You need this function in order to destroy all data Associate with a button:
void destroyChessLoadButton(ChessWidget*);

void handleChessLoadButtonEvenet(ChessWidget* src, SDL_Event* event);

void drawChessLoadButton(ChessWidget* src);

#endif //CHESS1_CHESSLOADBUTTON_H
